#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


static void bye_1(void)
{
    printf("Good Bye 1\n");
}

static void bye_2(void)
{
    printf("Good Bye 2\n");
}
static void bye_3(void)
{
    printf("Good Bye 3\n");
}



int main (void)
{
    /* Stack */
    atexit(bye_1);
    atexit(bye_2);
    atexit(bye_3);
    printf("Hello World~\n");


    sleep(2);
    exit(0);
    return 0;
}