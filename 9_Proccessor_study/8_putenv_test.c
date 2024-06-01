#include <stdio.h>
#include <stdlib.h> 

extern char **environ;


int main (int argc, char * argv[])
{
    int ret = 0;

    if(argc < 2 ) return 1;

    ret = putenv(argv[1]);
    if(ret)
    {
        perror("putenv Erorr");
        return 1;
    }

    for(int i = 0;environ[i] == NULL;i++)
    {
        printf("%s\n", environ[i]);
    }

    return 0;
}


