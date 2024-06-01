#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main (void)
{
    switch(vfork())
    {
        case -1 :
            perror("vfork Error");
            return 1;
        
        case 0 :
            printf("Child %d\n", getpid());
            _exit(0);

        default :
            printf("Parent %d\n", getpid());
            break;
    }


    exit(0);
    return 0;
}