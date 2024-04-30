#include <stdio.h>


int main (void)
{
    char buf[128] = {0};

    gets(buf);
    puts(buf);

    return 0;
}