#include <stdio.h>
#include <stdlib.h>

#include "stateSaver.h"

static char* folderPath = "beagle-gotchi-states/%s.dat";
static const int PATH_BUFFER_LENGTH = 100;

void StateSaver_loadModule(char* fileName, void* module, size_t size)
{
    char filePath[PATH_BUFFER_LENGTH];
    snprintf(filePath, PATH_BUFFER_LENGTH, folderPath, fileName);
    FILE *pFile = fopen(filePath, "r");

    if (!pFile) {
        printf("ERROR: Unable to open %s.\n", filePath);
        exit(1);
    }

    fread(module, size, 1, pFile);

    fclose(pFile);
    return;
}

void StateSaver_unloadModule(char* fileName, void* module, size_t size)
{
    char filePath[PATH_BUFFER_LENGTH];
    snprintf(filePath, PATH_BUFFER_LENGTH, folderPath, fileName);
    FILE *pFile = fopen(filePath, "w");

    if (!pFile) {
        printf("ERROR: Unable to open %s.\n", filePath);
        exit(1);
    }

    int charWritten = fwrite(module, size, 1, pFile);
    if (charWritten <= 0) {
        printf("ERROR: Cannot write %s.\n", filePath);
        exit(1);
    }

    fclose(pFile);
    return;
}