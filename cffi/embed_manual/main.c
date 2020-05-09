#include <stdio.h>
#include "plugin.h"

int main(int argc, char *argv[])
{
    point_t xy = {.x = 1, .y=2};
    
    printf("HELLO WORLD: %d", do_stuff(&xy));
    return 0;
}

