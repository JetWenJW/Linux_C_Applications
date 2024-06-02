#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

static char gpio_path[100];

static int gpio_config(const char *attr, const char *val)
{
    char file_path[100];
    int len;
    int fd;

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
    
    /* Close File */
    close(fd);
    return 0;
}

int main(int argc, char *argv[])
{
    /* Check Parameter */
    if(argc != 3)
    {
        fprintf(stderr, "usage: %s <gpio> <value>\n", argv[0]);
        exit(-1);
    }

    sprintf(gpio_path, "/sys/class/gpio/gpio%s", argv[1]);

    if(access(gpio_path, F_OK))
    {
        int fd, len;
    
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

    /* Configure GPIO as Output */
    if(gpio_config("direction", "out"))
    {
        exit(-1);
    }

    /* Set GPIO Property */
    if(gpio_config("active_low", "0"))
    {
        exit(-1);
    }

    /* Set GPIO as Low Voltage */
    if(gpio_config("value", argv[2]))
    {
        exit(-1);
    }

    /* Exit Program */
    exit(0);
}









