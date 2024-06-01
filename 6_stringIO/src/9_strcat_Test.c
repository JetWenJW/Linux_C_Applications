#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main (void)
{
    char *str = "World~";
    char buf[128] = {'H', 'e', 'l', 'l', 'o', ' '};

    strcat(buf, str);
    puts(buf);

    return 0;
}