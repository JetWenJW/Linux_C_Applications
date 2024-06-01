#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main (void)
{
    char buf[128] = {0};

    strcpy(buf, "Hello Jet~");
    puts(buf);

    return 0;
}