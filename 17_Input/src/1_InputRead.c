#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
    struct input_event in_ev = {0};
    int fd = -1;

    /* Check Parameter */
    if(argc != 2)
    {
        fprintf(stderr, "usage: %s <input-dev\n>", argv[0]);
	exit(-1);
    }

    while(1)
    {
        if(sizeof(struct input_event) != read(fd, &in_ev, sizeof(input_event)))
	{ 
	    perror("Read Error");
	    exit(-1);
	}

	printf("type: %d, code : %d, value: %d\n", in_ev.type, in_ev.code, in_ev.value);
    }
}




