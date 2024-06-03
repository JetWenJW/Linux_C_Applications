#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct input_event in_ev;
    int x, y, down, valid;
    int fd = -1;

    if(argc != 2)
    {
        fprintf(stderr, "usage: %s <input-dev>\n", argv[0]);
	exit(EXIT_FAILURE);
    }

    /* Open File */
    fd = open (argv[1], O_RDONLY);
    if(fd < 0)
    {
        perror("Open Error");
	exit(EXIT_FAILURE);
    }

    x = y = 0;
    down = -1;
    valid = 0;

    while(1)
    {
        if(sizeof(struct input_event) != read(fd, &in_ev, sizeof(struct input_event)))
	{
	    perror("Read Error");
	    exit(EXIT_FAILURE);
	}
    
        switch(in_ev.type)
	{
		case EV_KEY:
			if(BTN_TOUCH == in_ev.code)
			{
			    down = in_ev.value;
			    valid = 1;
			}
			break;
		case EV_ABS:
			switch(in_ev.code)
			{
				case ABS_X:
					x = in_ev.value;
					valid = 1;
					break;
				case ABS_Y:
					y = in_ev.value;
					valid = 1;
					break;
			}
			break;
		case EV_SYN:
			if(SYN_REPORT == in_ev.code)
			{
			    if(valid)
			    {
			   	switch(down)
			    	{
			    	case 1:
					printf("Press(%d, %d)\n", x, y);
					break;
				case 0:
					printf("Release\n");
					break;
				case -1:
					printf("Move(%d, %d)\n", x, y);
					break;
				}					    	
			    }	    
         		    	valid = 0;
				down = -1;
			}
	}
	break;
	}
    }
}



