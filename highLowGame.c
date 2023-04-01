#include <pthread.h>
#include <stdbool.h>

#include "utils.h"
#include "joystick.h"

// Game Thread
static void* hlGameThreadFunction(void* arg);
static pthread_t menuReaderThread;

static bool stopping;

void HighLowGame_init(void)
{
    stopping = false;
    pthread_create(&menuReaderThread, NULL, hlGameThreadFunction, NULL);
}

void HighLowGame_cleanup(void)
{
    stopping = true;
    pthread_join(menuReaderThread, NULL);
}

void* hlGameThreadFunction(void* arg)
{
    (void)arg;
    
    return NULL;
}