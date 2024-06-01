#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h> 



int main(int argc, char * argv[])
{
    struct flock lock = {0};
    int fd = -1;
    char buf[] = "Hello World!";

    /* Check Parameter  */
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(-1);
    }

    /* Open File */
    fd = open(argv[0], O_WRONLY);
    if(fd < 0)
    {
        perror("open Error");
        exit(-1);
    }

    /* Locke File */
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    if(fcntl(fd, F_SETLK, &lock) == -1)
    {
        perror("Lock Fail~");
        exit(-1);
    }

    printf("Lock File Succeed\n");

    /* Write File */
    if(write(fd, buf, strlen(buf)) < 0)
    {
        perror("Write Error");
        exit(-1);
    }

    /* Unlcok File */
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    /* Exit Function */
    close(fd);
    return 0;
}