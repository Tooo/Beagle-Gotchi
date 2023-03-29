#include <stdio.h>
#include "../shutdown.h"
#include "../menu.h"
#include "../menuReader.h"

// Initialize/cleanup the module's data structures.

int main(void)
{
    Menu_init();
    MenuReader_init();

    getchar();

    MenuReader_cleanup();
    Menu_cleanup();

    return 0;
}
