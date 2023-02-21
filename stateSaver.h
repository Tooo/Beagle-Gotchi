// stateSaver.h
// Save the states of modules
#include <string.h>

/*
 * Load and unload modules from file
 * - char* fileName: name of file 
 * -- (Folders and file type will be added in function)
 * - void* module: struct of module
 * - size_t size: size of struct
 */
void StateSaver_loadModule(char* fileName, void* module, size_t size);
void StateSaver_unloadModule(char* fileName, void* module, size_t size);