#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    int data;
    int buf1[25];
    int buf2[25];

    sscanf("100 Hello World~", "%d %s %s", &data, buf1, buf2);

    printf("%d\n", data);
    printf("%s\n", buf1);
    printf("%s\n", buf2);

    return 0;
}