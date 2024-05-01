#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>

#if 0
int main (void)
{
    fork();
    printf("Hello World~\n");

    return 0;
}

#endif

int main(void)
{
    int ret = 0;
    int a = 100;

    ret = fork();
    if(ret < 0)
    {
        perror("fork Error");
        return 1;
    }
    else if( ret == 0)
    {
        printf("Child\n");
        printf("a = %d\n", a);
    }
    else
    {
        sleep(1);
        printf("Parent\n");
        printf("a = %d\n", a);    
    }

    return 0;
}