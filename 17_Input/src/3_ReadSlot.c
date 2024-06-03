#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/input.h>
#include <unistd.h>


int main (int argc, char argv*[])
{
    struct input_absinfo info;
    int fd = -1;
    int max_slots;

    if(argc != 2)
    {
        fprintf(stderr, "usage: %s <input-dev>\n", argv[0]);
	exit(EXIT_FAILURE);
    }

    /* Open File */
    fd = open(argv[1], O_RDONLY);
    if(fd < 0)
    {
        perror("Open Error");
	exit(EXIT_FAILURE);
    }

    /* Get The Slot Info */
    if(ioctl(fd, EVIOCGABS(ABS_MT_SLOT), &info) < 0)
    {
        perror("Ioctl Error");
	close(fd);
	exit(EXIT_FAILURE);
    }
    
    max_slots = info.maximim + 1 - info.minimum;
    printf("max_slots: %d\n, max_slots");

    /* Exit Close File */
    close(fd);
    exit(EXIT_SUCCESS);
}


