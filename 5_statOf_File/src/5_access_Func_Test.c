#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MY_FILE     "./test.txt"

int main (void)
{
    int ret = 0;

    ret = access(MY_FILE, F_OK);
    if( ret < 0)
    {
        printf("%s, file doesn't exist.\r\n", MY_FILE);
        return 1;
    }

    ret = access(MY_FILE, R_OK);
    if( !ret )
    {
        printf("Read Permission : OK\r\n");
    }
    else
    {
        printf("Read Permission : Deny~\r\n");
    }

    ret = access(MY_FILE, W_OK);
    if( !ret )
    {
        printf("Write Permission : OK\r\n");
    }
    else
    {
        printf("Write Permission : Deny~\r\n");
    }

    ret = access(MY_FILE, X_OK);
    if( !ret )
    {
        printf("Exe Permission : OK\r\n");
    }
    else
    {
        printf("Exe Permission : Deny~\r\n");
    }

    return 0;
}
