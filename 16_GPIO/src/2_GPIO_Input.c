#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

static char gpio_path[100];

static int gpio_config(const char *attr, const char *val)
{
    int len, fd;
    char file_path[100];

    sprintf(file_path, "%s%s", gpio_path, attr);
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
    return (0);
}


int main(int argc, char *argv[])
{
    char file_path[100];
    char val;
    int fd;

    if(argc != 2)
    {
        fprintf(stderr, "usage: %s <gpio>\n", argv[0]);
	exit(-1);
    }

    sprintf(gpio_path, "sys/class/gpio/gpio%s", argv[1]);

    if(access(gpio_path, F_OK))
    {
        int len;
	fd = open("sys/class/gpio/export", O_WRONLY);
        if(fd < 0)
	{
	    perror("Open Error");
	    exit(-1);
	}

	len = strlen(argv[1]);
	if(len != write(fd, argv[1], len))
	{
	    perror("Write Error");
	    close(fd);
	    exit(-1);
	}
        close(fd);
    }

    /* Configured GPIO as Input */
    if(gpio_config("direction", "in"))
    {
        exit(-1);
    }

    /* Set Property */
    if(gpio_config("active low", "0"))
    {
        exit(-1);
    }

    /* Set Non-Interrupt */
    if(gpio_config("edge", "none"))
    {
        exit(-1);
    }

    /* Get GPIO Voltage */
    sprintf(file_path, "%s%s", gpio_path, "value");
    fd = open(file_path, O_RDONLY);
    if(fd < 0)
    {
        perror("Open Error");
    }

    if(read(fd, &val, 1) < 0)
    {
        perror("Read Error");
	close(fd);
        exit(-1);
    }

    printf("value: %c\n", val);

    /* Exit Program */
    close(fd);
    exit(0);
}


