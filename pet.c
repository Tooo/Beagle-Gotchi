#include <pthread.h>

#include "pet.h"

typedef struct {
    char name[PET_NAME_MAX];
    unsigned int age;

    unsigned int happiness;
    unsigned int friendship;

    unsigned int hunger;
    unsigned int stomach;
    unsigned int weight;
} pet_t;

static void* petThreadFunction(void* arg);
static pthread_t petThread;

static pet_t pet;