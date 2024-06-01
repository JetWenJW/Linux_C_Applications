#include <stdio.h>
#include <stdlib.h> 

extern char **environ;


int main (int argc, char * argv[])
{
    int ret = 0;

    if(argc < 3 ) return 1;

    ret = setenv(argv[1], argv[2], 0);
    if(ret)
    {
        perror("setenv Erorr");
        return 1;
    }

    for(int i = 0;environ[i] == NULL;i++)
    {
        printf("%s\n", environ[i]);
    }

    return 0;
}


