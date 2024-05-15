#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/file.h> 
#include <signal.h> 
#include <string.h>


int main(int argc, char * argv[])
{
    char buf[100] = "Hello World ~";
    int fd = 0;
    int len = 0;

    if(argc != 2)
    {
        fprintf(stderr, "Usage : %s <file>\n", argv[0]);
        exit(-1);
    }

    /* Open File */
    fd = open(argv[1], O_RDWR);
    if(fd == -1)
    {
        perror("open Error");
        exit(-1);
    }

    /* Use NonBlocking Method to Lock File */
    if(flock(fd, LOCK_EX | LOCK_NB) == -1)
    {
        perror("Proccessor_2: File Lock Fail");
    }
    else
    {
        printf("Proccessor_2: File Lock Succeed\n");
    }

    /* Write File */
    len = strlen(buf);
    if(write(fd, buf, len) < 0)
    {
        perror("write Erorr");
        exit(-1);
    }
    printf("Proccessor_2: Write String to file <%s>\n", buf);

    /* Move Pointer to head of file */
    if(lseek(fd, 0x00, SEEK_SET) < 0)
    {
        perror("lseek Error");
        exit(-1);
    }

    /* Read File */
    memset(buf, 0x00, sizeof(buf));
    if(read(fd, buf, len) < 0)
    {
        perror("read Error");
        exit(-1);
    }

    printf("Proccessor_2: Read String From File <%s>\n", buf);

    /* Unlock & Exit */
    flock(fd, LOCK_UN);
    close(fd);
    return 0;
}





