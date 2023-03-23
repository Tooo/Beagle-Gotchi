#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "menu.h"
#include "utils.h"

#define JSUP_FILEPATH "/sys/class/gpio/gpio26/value"
#define JSDN_FILEPATH "/sys/class/gpio/gpio46/value"
#define JSLFT_FILEPATH "/sys/class/gpio/gpio65/value"
#define JSRT_FILEPATH "/sys/class/gpio/gpio47/value"
#define JSPB_FILEPATH "/sys/class/gpio/gpio27/value"
#define JSUP_CONFIG_GPIO_COMMAND "config-pin p8.14 gpio"
#define JSDN_CONFIG_GPIO_COMMAND "config-pin p8.16 gpio"
#define JSLFT_CONFIG_GPIO_COMMAND "config-pin p8.18 gpio"
#define JSRT_CONFIG_GPIO_COMMAND "config-pin p8.15 gpio"
#define JSPB_CONFIG_GPIO_COMMAND "config-pin p8.17 gpio"

int buttonsFlag; // Set to 0 when done
pthread_t buttons_thread;

static void *Buttons_thread() 
{
    // Call config on all the buttons
    runCommand(JSUP_CONFIG_GPIO_COMMAND);
    runCommand(JSDN_CONFIG_GPIO_COMMAND);
    runCommand(JSLFT_CONFIG_GPIO_COMMAND);
    runCommand(JSRT_CONFIG_GPIO_COMMAND);
    runCommand(JSPB_CONFIG_GPIO_COMMAND);

    while(buttonsFlag) {
        // Check for any gpio values
        char allGpioValues[5][30] = {JSUP_FILEPATH, JSDN_FILEPATH, JSLFT_FILEPATH, JSRT_FILEPATH, JSPB_FILEPATH};
        for (int i=0; i<5; i++){
            if (!readIntFromFile(allGpioValues[i])) {
                // Process
                if (strcmp(allGpioValues[i],JSUP_FILEPATH) == 0) {
                    Menu_moveHighlighted(0);
                }
                else if (strcmp(allGpioValues[i],JSDN_FILEPATH) == 0) {
                    Menu_moveHighlighted(1);
                }
                else if (strcmp(allGpioValues[i],JSLFT_FILEPATH) == 0) {
                    Menu_moveHighlighted(2);
                }
                else if (strcmp(allGpioValues[i],JSRT_FILEPATH) == 0) {
                    Menu_moveHighlighted(3);
                }
                else if (strcmp(allGpioValues[i],JSPB_FILEPATH) == 0) {
                    Menu_selectOption();
                }
                Menu_printOptions();

                // Wait for the gpio value to reset before checking for another input
                while(!readIntFromFile(allGpioValues[i])) {
                    sleep(1); // Check every 1 second
                }
            }
        }
    }

    // Shut down
    return NULL;
}

void Buttons_init()
{
    buttonsFlag = 1;
    pthread_create(&buttons_thread, NULL, Buttons_thread, NULL);
}


void Buttons_cleanup(void)
{
    buttonsFlag = 0; 
    pthread_join(buttons_thread, NULL);
}