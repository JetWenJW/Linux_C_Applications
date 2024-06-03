#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

static char pwm_path[] = "/sys/class/pwm/pwmchip4/pwm2";

static int pwm_config(const char * attr, const char * val)
{
    char file_path[100];
    int len;
    int fd;

    sprintf(file_path, "%s%s", pwm_path, attr);
    fd = open(file_path, O_WRONLY);
    if(fd < 0)
    {
        perror("Open Error");
	return fd;
    }

    len = strlen(val);
    if(len != write(fd, val, len))
    {
        perror("Write Error");
	close(fd);
	return -1;
    }

    close(fd);
    return 0;
}


int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        fprintf(stderr, "usage: %s <period> <duty>\n", argv[0]);
	exit(-1);
    }

    printf("PWM config: period<%s>, duty<%s>\n", argv[1], argv[2]);

    if(access(pwm_path, F_OK))
    {
        int fd = open("/sys/class/pwm/pwmchip4/export", O_WRONLY);
	if(fd < 0)
	{
	    perror("Open Error");
	    exit(-1);
	}
    
        if(write(fd, "2", 1) != 1)
	{
	    perror("Write Error");
	    close(fd);
	    exit(-1);
	}
    
        close(fd);
    }

    /* Set PWM Period */
    if(pwm_config("period", argv[1])) exit(-1);

    /* Set Duty Cycle */
    if(pwm_config("duty_cycle", argv[2])) exit(-1);

    /* Enable PWM */
    pwm_config("enable", "1");

    exit(0);
}








