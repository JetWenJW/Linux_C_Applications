#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>


int main(int argc, char *argv[])
{
    struct input_event in_ev = {0};
    int fd = -1;
    int value = -1;

    /* Check Parameter */
    if(argc != 2)
    {
        fprintf(stderr, "usage: %s <input-dev>\n", argv[0]);
	exit(-1);
    }

    /* Open File */
    fd = open(argv[1], O_RDONLY);
    if(fd < 0)
    {
        perror("Open Error");
	exit(-1);
    }

    while(1)
    {
        /* Read Data */
        if(sizeof(struct input_event) != read(fd, &in_ev, sizeof(struct input_event)))
	{
	    perror("Read Error");
	    exit(-1);
	}
        
	if(EV_KEY == in_ev.type)	/* Key Event */
        {
	    switch(in_ev.value)
	    {
	        case 0:
		    printf("code<%d>: Release\n", in_ev.code);
		    break;

		case 1:
		    printf("code<%d>: Press\n", in_ev.code);
		    break;
		case 2:
		    printf("code<%d>: Hold\n", in_ev.code);
	    	    break;
	    }
	}
    }
}

