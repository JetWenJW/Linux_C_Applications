#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/watchdog.h>

#define WDOG_DEV "/dev/watchdog"

int main(int argc, char *argv[])
{
    struct watchdog_info info;
    int timeout, time, fd, op;

    if(2 != argc)
    {
        fprintf(stderr, "Usage : %s<timeout>\n", argv[0]);
	exit(EXIT_FAILURE);
    }

    /* Enable WatchDog */
    fd = open(WDOG_DEV, O_RDWR);
    if(fd < 0)
    {
        fprintf(stderr, "Open Error : %s: %s\n", strerror(errno));
	exit(EXIT_FAILURE);
    }

    /* WE need to stop WDOG when we just Open It */
    op = WDIOS_DISABLECARD;
    if(ioctl(fd, WDIOC_SETOPTIONS, &op) < 0)
    {
	    fprintf(stderr, "ioctl Error: WDIOC_SETOPTIONS: %s\n", strerror(errno));
    	    close(fd);
	    exit(EXIT_FAILURE);
    }

    timeout = atoi(argv[1]);
    if(timeout < 1)
    {
        timeout = 1;
    }

    /* Set timeout */
    if(ioctl(fd, WDIOC_SETTIMEOUT, &timeout))
    {
        fprintf(stderr, "ioctl Error: WDIOC_SETTIMEOUT: %s\n", strerror(errno));
	close(fd);
	exit(EXIT_FAILURE);
    }

    /* OPen WDOG Timer */
    op = WDIOS_ENABLECARD;
    if(ioctl(fd, WDIOC_SETOPTIONS, &op) < 0)
    {
        fprintf(stderr, "ioctl Error: WDIOC_SETOPTIONS: %s\n", strerror(errno));
	close(fd);
	exit(EXIT_FAILURE);
    }

    /* Feed Dog */
    time = (timeout * 1000 - 100) * 1000;
    while(1)
    {
        usleep(time);
	ioctl(fd, WDIOC_KEEPALIVE, NULL);
    }
}

