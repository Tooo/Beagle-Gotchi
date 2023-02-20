#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "menu.h"

#define JSUP_FILEPATH "/sys/class/gpio/gpio26/value"
#define JSDN_FILEPATH "/sys/class/gpio/gpio46/value"
#define JSLFT_FILEPATH "/sys/class/gpio/gpio65/value"
#define JSRT_FILEPATH "/sys/class/gpio/gpio47/value"
#define JSUP_CONFIG_GPIO_COMMAND "config-pin p8.14 gpio"
#define JSDN_CONFIG_GPIO_COMMAND "config-pin p8.16 gpio"
#define JSLFT_CONFIG_GPIO_COMMAND "config-pin p8.18 gpio"
#define JSRT_CONFIG_GPIO_COMMAND "config-pin p8.15 gpio"

int buttonsFlag = 1; // Set to 0 when done

// Runs the string command 
static void run_command(char *command)
{
  // Execute the shell command (output into pipe)
  FILE *pipe = popen(command, "r");
  // Ignore output of the command ; but consume it  so no error
  char buffer[1024];
  while (!feof(pipe) && !ferror(pipe))
  {
    if (fgets(buffer, sizeof(buffer), pipe) == NULL)
      break;
  }

  int exitCode = WEXITSTATUS(pclose(pipe));
  if (exitCode != 0)
  {
    perror("Unable to execute command:");
    printf("   command:    %s\n", command);
    printf("   exit code:  %d\n", exitCode);
  }
}

// Gets the gpio value from value file and returns 0 or 1 if pressed or not
static int read_gpio_file_to_int(char *fileName)
{
  FILE *pFile = fopen(fileName, "r");
  if (pFile == NULL)
  {
    printf("ERROR: Unable to open file (%s) for read\n", fileName);
    exit(-1);
  }
  // Read string (line)
  const int MAX_LENGTH = 1024;
  char buff[MAX_LENGTH];
  fgets(buff, MAX_LENGTH, pFile);
  // Close
  fclose(pFile);
  // Inspired by geeksforgeeks.org/c-program-for-char-to-int-conversion
  int x;
  sscanf(buff, "%d", &x);
  return x;
}

void *init_buttons(MenuOptionNode *mainMenu) 
{
    // Call config on all the buttons
    run_command(JSUP_CONFIG_GPIO_COMMAND);
    run_command(JSDN_CONFIG_GPIO_COMMAND);
    run_command(JSLFT_CONFIG_GPIO_COMMAND);
    run_command(JSRT_CONFIG_GPIO_COMMAND);

    while(buttonsFlag) {
        // Check for any gpio values
        char allGpioValues[4][30] = {JSUP_FILEPATH, JSDN_FILEPATH, JSLFT_FILEPATH, JSRT_FILEPATH};
        for (int i=0; i<4; i++){
            if (!read_gpio_file_to_int(allGpioValues[i])) {
                // Process
                if (strcmp(allGpioValues[i],JSUP_FILEPATH) == 0) {
                    move_highlighted(mainMenu->options, 0);
                }
                else if (strcmp(allGpioValues[i],JSDN_FILEPATH) == 0) {
                    move_highlighted(mainMenu->options, 1);
                }
                else if (strcmp(allGpioValues[i],JSLFT_FILEPATH) == 0) {
                    move_highlighted(mainMenu->options, 2);
                }
                else if (strcmp(allGpioValues[i],JSRT_FILEPATH) == 0) {
                    move_highlighted(mainMenu->options, 3);
                }
                print_menu_options(mainMenu);

                // Wait for the gpio value to reset before checking for another input
                while(!read_gpio_file_to_int(allGpioValues[i])) {
                    sleep(1); // Check every 1 second
                }
            }
        }
    }


    // Shut down
    return NULL;
}

void cleanup_buttons(void)
{
    buttonsFlag = 0; 
}

