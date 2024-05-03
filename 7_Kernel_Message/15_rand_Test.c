#include <stdlib.h>
#include <stdio.h>

int main (void)
{
    int ret = 0;

    for(int i = 0;i < 10;i++)
    {
        ret = rand();
        printf("%d\r\n", ret);
    }

    return 0;
}