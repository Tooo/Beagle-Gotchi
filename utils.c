#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

// ------------------------------- //
// globals:

#define GPIO_PATH "/sys/class/gpio/"

// ------------------------------- //
// provided utils:

long long getTimeInMs(void) {
    struct timespec spec;
    // if you have an error here, assign "cStandard": "gnu99", in `.vscode/c_cpp_properties.json`
    clock_gettime(CLOCK_REALTIME, &spec);
    long long seconds = spec.tv_sec;
    long long nanoSeconds = spec.tv_nsec;
    long long milliSeconds = seconds * 1000 + nanoSeconds / 1000000;
    return milliSeconds;
}

void sleepForMs(long long delayInMs) {
    const long long NS_PER_MS = 1000 * 1000;
    const long long NS_PER_SECOND = 1000000000;
    long long delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *) NULL);
}

void runCommandExtra(const char* command, bool suppressError) {
    // Execute the shell command (output into pipe)
    FILE *pipe = popen(command, "r");
    // Ignore output of the command; but consume it
    // so we don't get an error when closing the pipe.
    char buffer[1024];
    while (!feof(pipe) && !ferror(pipe)) {
        if (fgets(buffer, sizeof(buffer), pipe) == NULL)
            break;
        // printf("--> %s", buffer); // Uncomment for debugging
    }
    
    // Get the exit code from the pipe; non-zero is an error:
    int exitCode = WEXITSTATUS(pclose(pipe));

    if (suppressError) 
        return;
        
    if (exitCode != 0) {
        //perror("Unable to execute command:");
        printf("Unable to execute command:");
        printf(" command: %s\n", command);
        printf(" exit code: %d\n", exitCode);
    }
}
void runCommand(const char* command) {
    runCommandExtra(command, false);
}

// ------------------------------- //
// custom utils:

int readIntFromFile(const char* path) {
    FILE* fp = fopen(path, "r");
    if (fp == NULL) { printf("Error reading file %s\n", path); exit(-1); }

    // read line (should be a single int)
    const int MAX_LINE_LEN = 64;
    char fileBuf[MAX_LINE_LEN];
    fgets(fileBuf, MAX_LINE_LEN, fp);

    fclose(fp);

    return atoi(fileBuf);  
}

void writeIntToFilePointer(FILE* fp, int val) {
    const int MAX_LINE_LEN = 20; // fits 9,223,372,036,854,775,807
    // NOTE: could make this array static if its only used by 1 thread
    char valStrBuf[MAX_LINE_LEN]; 
    sprintf(valStrBuf, "%d", val);
    fwrite(valStrBuf, 1, strlen(valStrBuf), fp);
}

void writeIntToFile(const char* path, int val) {
    FILE* fp = fopen(path, "w");
    if (fp == NULL) { printf("Error writing file %s\n", path); exit(-1); }

    // write int
    writeIntToFilePointer(fp, val);
    fclose(fp);
}

void silentTryWriteIntToFile(const char* path, int val) {
    FILE* fp = fopen(path, "w");
    if (fp != NULL) {
        writeIntToFilePointer(fp, val);
        fclose(fp);
    }
}

// helpful oneliner derived from: 
// https://stackoverflow.com/questions/4770985/how-to-check-if-a-string-starts-with-another-string-in-c
bool startswith(const char* prefix, const char* str) {
    return strncmp(prefix, str, strlen(prefix)) == 0;
}

// returns true if the pin was changed, and false if otherwise
bool exportGpio(int pinNum) {
    char fileNameBuf[256];
    sprintf(fileNameBuf, GPIO_PATH "gpio%d", pinNum);
    if (access(fileNameBuf, F_OK) == 0) {
        printf("%s exists\n", fileNameBuf);
        return false;
    } else {
        printf("%s doesn't exist\n", fileNameBuf);
        // Export the gpio pins
        FILE *gpioExP = fopen(GPIO_PATH "export", "w");
        if (gpioExP == NULL) {
            printf("ERROR: Unable to open export file.\n");
            return false; //exit(-1);
        } else {
            fprintf(gpioExP, "%d", pinNum);
            fclose(gpioExP);
        
            return true;
        }
    }
}

void setGpioDirection(int pinNum, const char* direction) {
    // Change the direction into out
    char fileNameBuffer[256];
    sprintf(fileNameBuffer, GPIO_PATH "gpio%d/direction", pinNum);
        
    FILE *gpioDirP = fopen(fileNameBuffer, "w");
    fprintf(gpioDirP, direction);
    fclose(gpioDirP);
}