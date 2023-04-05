// stateSaver.h
// Save the states of modules
#ifndef STATE_SAVER_H
#define STATE_SAVER_H

#include <string.h>
#include <stdbool.h>

/*
 * Load and unload modules from file
 * - char* fileName: name of file 
 * -- (Folders and file type will be added in function)
 * - void* module: struct of module
 * - size_t size: size of struct
 */
void StateSaver_loadModule(const char* fileName, void* module, size_t size);
void StateSaver_unloadModule(const char* fileName, void* module, size_t size);

// Check if state file exist
// Return true if it does exist
bool StateSaver_stateExist(const char* fileName);

#endif