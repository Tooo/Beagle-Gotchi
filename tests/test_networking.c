#include <stdio.h>

#include "../utils/shutdown.h"
#include "../utils/networking.h"
#include "../pet/pet.h"
#include "../utils/utils.h"

int main(void)
{
    Pet_init(false);
    udp_init();
    getchar();
    udp_clean_up();
    Pet_cleanup();


    return 0;
}
