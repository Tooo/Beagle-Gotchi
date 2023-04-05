#include <pthread.h>
#include <string.h>
#include <unistd.h>

#include "pet.h"
#include "utils.h"
#include "terminal.h"
#include "stateSaver.h"
#include "shutdown.h"

#include "buzzer.h"
#include "joystick.h"
#include "ledMatrix/ledMatrix.h"

typedef struct {
    char name[PET_NAME_MAX];
    int age;

    int mood;
    int friendship;

    int hunger;
    int weight;
} pet_t;

static pet_t pet;

#define PET_STAT_MAX 1000

static int stageRange[STAGE_COUNT-1] = {10, 50, 100, 200};

static char* petFileHeader = "pet_%s";

#define PET_SLEEP_MS 1000

static void* petThreadFunction(void* arg);
static pthread_t petThread;
static bool stopping;

bool applyJoystick(int* index, char* shortName) 
{
    bool doneNaming = false;
    int i = *index;

    JoystickDirection dir = Joystick_getDirection();
    if (dir == JOYSTICK_UP) {
        if (shortName[i] == ' ') {
            shortName[i] = 'a';
        } else if (shortName[i] == 'z') {
            shortName[i] = ' ';
        } else {
            shortName[i] = shortName[i] + 1;
        }
        
        Buzzer_playNote(BUZZER_NOTE_D, 80);
        ledMatrix_drawVLine(WHITE, i * 4, 6, 3);
        sleepForMs(200-80);

    } else if (dir == JOYSTICK_DOWN) {
        if (shortName[i] == ' ') {
            shortName[i] = 'z';
        } else if (shortName[i] == 'a') {
            shortName[i] = ' ';
        } else {
            shortName[i] = shortName[i] - 1;
        }
        
        Buzzer_playNote(BUZZER_NOTE_D, 80);
        ledMatrix_drawVLine(WHITE, i * 4, 6, 3);
        sleepForMs(200-80);

    } else if (dir == JOYSTICK_LEFT) {
        ledMatrix_drawVLine(BLACK, i * 4, 6, 3);

        *index -= 1;
        i = *index;
        if (i < 0) { 
            *index = 0;
            i = 0;
        }
        
        Buzzer_playNote(BUZZER_NOTE_G, 80);
        ledMatrix_drawVLine(WHITE, i * 4, 6, 3);
        sleepForMs(200-80);

    } else if (dir == JOYSTICK_RIGHT) {
        ledMatrix_drawVLine(BLACK, i * 4, 6, 3);

        *index += 1;
        i = *index;
        if (i >= 8) { 
            *index = 7;
            i = 7;
            if (strcmp(shortName, "        ") == 0) {
                ledMatrix_drawString("bad name", 0, 12, RED);
                sleepForMs(400);

            } else {
                doneNaming = true;
            }
        }
        
        Buzzer_playNote(BUZZER_NOTE_G, 80);
        ledMatrix_drawVLine(WHITE, i * 4, 6, 3);
        sleepForMs(200-80);
    }

    return doneNaming;
}

void Pet_init()
{
    char name[PET_NAME_MAX];
    char fileName[FILENAME_MAX];
    memset(name, 0, sizeof(name));
    memset(fileName, 0, sizeof(fileName));

    if (isDebugMode()) {
        // get input from terminal
        Terminal_inputPetName(name);
        snprintf(fileName, FILENAME_MAX, petFileHeader, name);
        
    } else {
        sleepForMs(400);
        ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED);

        const char* meta_filename = "beagle-gotchi-states/meta.txt";

        // check if meta.txt exists
        if (access(meta_filename, F_OK) == 0) {
            readLineFromFile("beagle-gotchi-states/meta.txt", name, PET_NAME_MAX);
            snprintf(fileName, FILENAME_MAX, petFileHeader, name);

        } else {
            unsigned long long frame = 0;
            int i = 0;
            char shortName[9] = "        ";

            const int POLL_SPEED_MS = 50;
            bool doneNaming = false;
            while (!doneNaming) {
                ledMatrix_fillScreen(BLACK);

                // ask user to input name using joystick
                ledMatrix_drawString("name pet", 0, 0, GREEN);
                ledMatrix_drawHLine(GREEN, 1, 4, 29);
                ledMatrix_drawString(shortName, 1, 6, YELLOW);

                // render cursor
                if (between(frame % 10, 0, 4)) {
                    ledMatrix_drawVLine(WHITE, i * 4, 6, 3);
                }

                doneNaming = applyJoystick(&i, shortName);

                sleepForMs(POLL_SPEED_MS);
                frame += 1;
            }

            // convert trailing spaces into NULLs when moving shortName to name
            bool hitLetter = false;
            for (; i >= 0; i--) {
                if (hitLetter == false && shortName[i] == ' ') {
                    name[i] = '\0';
                } else {
                    hitLetter = true;
                    name[i] = shortName[i];
                }
            }

            writeLineToFile("beagle-gotchi-states/meta.txt", name);
            snprintf(fileName, FILENAME_MAX, petFileHeader, name);
            
            // the lick
            Buzzer_playNote(BUZZER_NOTE_D, 100);
            Buzzer_playNote(BUZZER_NOTE_E, 100);
            Buzzer_playNote(BUZZER_NOTE_F, 100);
            Buzzer_playNote(BUZZER_NOTE_G, 100);
            Buzzer_playNote(BUZZER_NOTE_E, 100);
            sleepForMs(100);
            Buzzer_playNote(BUZZER_NOTE_C, 100);
            Buzzer_playNote(BUZZER_NOTE_D, 100);

            ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED);
        }
    }

    if (StateSaver_stateExist(fileName)) {
        ledMatrix_drawString("loading", 0, 0, GREEN);
        sleepForMs(200);
        ledMatrix_drawString("pet", 0, 4, GREEN);
        sleepForMs(200);
        ledMatrix_drawString(name, 0, 8, WHITE);
        sleepForMs(900);

        Terminal_printLoadedPetMsg(name);
        Pet_loadPet(name);
    } else {
        ledMatrix_drawString("creating", 0, 0, GREEN);
        sleepForMs(200);
        ledMatrix_drawString("pet", 0, 4, GREEN);
        sleepForMs(200);
        ledMatrix_drawString(name, 0, 8, WHITE);
        sleepForMs(900);

        Terminal_printNewPetMsg(name);
        Pet_createPet(name);
    }

    pthread_create(&petThread, NULL, petThreadFunction, NULL);
    stopping = false;
}

void Pet_cleanup()
{
    stopping = true;
    pthread_join(petThread, NULL);
    Pet_unloadPet();
}

void Pet_createPet(const char* name)
{
    strncpy(pet.name, name, PET_NAME_MAX);
    pet.age = 0;
    pet.mood = PET_STAT_MAX/2;
    pet.friendship = 0;
    pet.hunger = PET_STAT_MAX/2;
    pet.weight = 10;
}

void Pet_loadDefault()
{
    Pet_loadPet("default");
}

void Pet_loadPet(const char* name)
{
    char fileName[PET_NAME_MAX];
    snprintf(fileName, PET_NAME_MAX, petFileHeader, name);

    StateSaver_loadModule(fileName, &pet, sizeof(pet));
}

void Pet_unloadPet()
{
    char fileName[FILENAME_MAX];
    snprintf(fileName, PET_NAME_MAX, petFileHeader, pet.name);

    StateSaver_unloadModule(fileName, &pet, sizeof(pet));
}

void Pet_getName(char* buffer)
{
    strncpy(buffer, pet.name, PET_NAME_MAX);
}

void Pet_setName(char* name)
{
    strncpy(pet.name, name, PET_NAME_MAX);
}

int Pet_getAge()
{
    return pet.age;
}

PetStage Pet_getStage()
{
    int stage = 0;
    for (int i = 0; i < STAGE_COUNT-1; i++) {
        if (pet.age < stageRange[i]) {
            return stage;
        }
        stage++;
    }
    return stage;
}

PetMood Pet_getMood()
{
    return pet.mood / (PET_STAT_MAX/MOOD_COUNT);
}

int Pet_getMoodNum()
{
    return pet.mood;
}

void Pet_addMood(int value)
{
    pet.mood += value;
    if (pet.mood < 0) {
        pet.mood = 0;
    }   else if (pet.mood > PET_STAT_MAX) {
        pet.mood = PET_STAT_MAX;
    }
}

PetFriendship Pet_getFriendship()
{
    return pet.friendship / (PET_STAT_MAX/FRIEND_COUNT);
}

int Pet_getFriendshipNum()
{
    return pet.friendship;
}

void Pet_addFriendship(int value)
{
    pet.friendship += value;
    if (pet.friendship < 0) {
        pet.friendship = 0;
    }   else if (pet.friendship > PET_STAT_MAX) {
        pet.friendship = PET_STAT_MAX;
    }
}

PetHunger Pet_getHunger()
{
    return pet.hunger / (PET_STAT_MAX/HUNGER_COUNT);
}

int Pet_getHungerNum()
{
    return pet.hunger;
}

void Pet_addHunger(int value)
{
    pet.hunger += value;
    if (pet.hunger < 0) {
        pet.hunger = 0;
    }   else if (pet.hunger > PET_STAT_MAX) {
        pet.hunger = PET_STAT_MAX;
    }
}

int Pet_getWeight()
{
    return pet.weight;
}

void Pet_addWeight(int value)
{
    pet.weight += value;
}

static void* petThreadFunction(void* arg)
{
    (void)arg;

    while (!stopping) {
        if (pet.hunger > 0) {
            pet.hunger--;
        }

        if (pet.mood > 0) {
            pet.mood--;
        }

        pet.age++;
        sleepForMs(PET_SLEEP_MS);
    }
    return NULL;
}