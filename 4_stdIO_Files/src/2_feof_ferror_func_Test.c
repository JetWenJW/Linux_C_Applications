#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void)
{
    FILE *f = NULL;
    int ret = 0;
    char buf[128] = {0};
    f = fopen("./test.txt", "w+");
    if(f = NULL)
    {
        perror("fopen Error");
        return 1;
    }

    ret = fwrite("Hello World~", 1, 12, f);
    if(ret < 12)
    {
        printf("fwrite Error\r\n");
        fclose(f);
        return 1;
    }

    ret = fseek(f, 0, SEEK_SET);
    if(ret < 0)
    {
        perror("fseek error");
        fclose(f);
        return 1;
    }

    ret = fread(buf, 1, 12, f);
    if(ret < 12)
    {
        if(ferror(f))
        {
            printf("fread Error\r\n");
            fclose(f);
            return 1;
        }
        else 
        {   if(feof(f))
            {
                printf("fread end-of-file\r\n");
                fclose(f);
                return 1;
            }
        }
        clearerr(f);
    }
    printf("fread : %s\r\n", buf);
    fclose(f);
    return 0;

}




