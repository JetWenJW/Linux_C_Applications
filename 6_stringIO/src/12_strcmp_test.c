#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (void)
{
    printf("%d\r\n", strcmp("ABC", "ABC"));
    printf("%d\r\n", strcmp("ABC", "a"));
    printf("%d\r\n", strcmp("a", "ABC"));

    return 0;

}