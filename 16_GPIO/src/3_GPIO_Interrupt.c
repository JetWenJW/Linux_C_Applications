#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <poll.h>
#include <string.h>
#include <unistd.h>


static char gpio_path[100];

static int gpio_config(const char * attr, const char *val)
{
    char file_path[100];
    int len, fd;

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
	return -1;
    }

    close(fd);
    return 0;
}

int main(int argc, char * argv[])
{
    struct pollfd pfd;
    char file_path[100];
    int ret = 0;
    char val;

    /* Check Parameter */
   if(argc != 2)
   {
       fprintf(stderr, "usage: %s <gpio>\n", argv[0]);
       exit(-1);
   }

   sprintf(gpio_path, "sys/class/gpio/gpio%s", argv[1]);

   if(access(gpio_path, F_OK))
   {
       int len, fd;

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
   if(gpio_config("active_low", "0"))
   {
        exit(-1);
   }

   /* Set Both Edge Trigger Interrupt */
   if(gpio_config("edge", "both"))
   {
       exit(-1);
   }

   sprintf(file_path, "%s%s", gpio_path, "value");
   pfd.fd = open(file_path, O_RDONLY);
   if(pfd.fd < 0)
   {
       perror("Open Error");
       exit(-1);
   }

   /* Call Poll */
   pfd.events = POLLPRI;
   
   read(pfd.fd, &val, 1);
   while(1)
   {
       ret = poll(&pfd, 1, -1);
       if(ret < 0)
       {
           perror("Poll Error");
	   exit(-1);
       }
       else if(ret == 0)
       {
           fprintf(stderr, "poll timeout\n");
	   continue;
       }
   
       if(pfd.revents & POLLPRI)
       {
	   /* Move Read Position to Head of File */
           if(lseek(pfd.fd, 0, SEEK_SET) < 0)
	   {
	       perror("lseek Error");
	       exit(-1);
	   }

	   if(read(pfd.fd, &val, 1) < 0)
	   {
	       perror("Read Error");
	       exit(-1);
	   }

	   printf("GPIO Interrupt Trigger <value = %c\n>", val);
       }
   }  
   exit(0);
}
