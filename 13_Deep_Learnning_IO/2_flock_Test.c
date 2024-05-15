#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/file.h> 
#include <signal.h> 

static int fd = -1;

static void signal_handler(int sig)
{
    if (SIGINT != sig) return;

    /* Unlock */
    flock(fd, LOCK_UN);
    close(fd);
    printf("Proccessor_1: File unlocked~\n");
}

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s<file>\n", argv[0]);
        exit(-1);
    }

    /* Open file */
    fd = open(argv[1], O_WRONLY);
    if(fd == -1)
    {
        perror("open Error");
        exit(-1);
    }

    /* Use NonBlock Method to Locked File  */
    if(flock(fd, LOCK_EX | LOCK_NB) == -1)
    {
        perror("Processor_1: File Lock Fail~");
        exit(-1);
    }

    printf("Proccessoe_1: File Lock Succeed~\n");

    /* Registry a SIGANL Handler */
    signal(SIGINT, signal_handler);

    while(1)
    {
        sleep(1);
    }




}





