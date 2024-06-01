#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main (void)
{
    char buffer[128] = {0};
    snprintf(buffer, 128, "Hello World~%d", 200);
    printf("%s\r\n", buffer);
    return 0;
}