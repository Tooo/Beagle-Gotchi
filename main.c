// main.c
// Main Thread of Beagle Gotchi
#include <stdio.h>


#include "shutdown.h"
<<<<<<< HEAD
#include "menu.h"
#include "buttons.h"
=======
#include "pet.h"
#include "petScreen.h"
>>>>>>> 0ced8ba901ab8db0e304a12120ff0ef475435346

// Initialize/cleanup the module's data structures.
// static void main_init(void);
// static void main_cleanup(void);
void print1(void);
void print2(void);
void print3(void);
void print4(void);

<<<<<<< HEAD

=======
static void main_init(void)
{
    Pet_init();
    PetScreen_init();
}
>>>>>>> 0ced8ba901ab8db0e304a12120ff0ef475435346

int main(void)
{
<<<<<<< HEAD
    Menu_init();
    Buttons_init();
    getchar();
    Buttons_cleanup();
    Menu_cleanup();

    return 0;
}
=======
    PetScreen_cleanup();
    Pet_cleanup();
}
>>>>>>> 0ced8ba901ab8db0e304a12120ff0ef475435346
