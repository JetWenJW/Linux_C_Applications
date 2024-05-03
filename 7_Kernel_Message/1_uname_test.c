#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>


int main (void)
{
    int ret = 0;
    struct utsname info = {0};

    ret = uname(&info);
    if(ret < 0 )
    {
        perror("uname Error");
        return 1;
    }

    printf("Operating System : %s\n", info.sysname);
    printf("Master Device : %s\n", info.nodename);
    printf("Kernel Ver. : %s\n", info.release);
    printf("Release Ver.: %s\n", info.version);
    printf("Hardware Arch : %s\n", info.machine);
    return 0;
}