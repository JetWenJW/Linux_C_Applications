#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void)
{
    struct stat st;
    int ret = 0;
    int fd;

    fd = open ("./test.txt", O_RDWR);
    if(ret < 0)
    {
        perror("open Error");
        return 1;
    }

    ret = fstat(fd, &st);
    if(ret < 0)
    {
        perror("Stat Error");
        close(fd);
        return 1;
    }

    printf("inode: %ld\r\n", st.st_ino);
    printf("size : %ld\r\n", st.st_size);
    printf("type: \r\n");

    if(S_ISREG(st.st_mode))
    {
        printf("Regular filer\r\n");
    }
    else if(S_ISDIR(st.st_mode))
    {
        printf("directory\r\n");
    }
    else if(S_ISCHR(st.st_mode))
    {
        printf("Chr Dev\r\n");
    }
    else if(S_ISBLK(st.st_mode))
    {
        printf("Block Dev\r\n");
    }
    else if(S_ISFIFO(st.st_mode))
    {
        printf("Pipe\r\n");
    }
    else if(S_ISLNK(st.st_mode))
    {
        printf("Link\r\n");
    }
    else if(S_ISSOCK(st.st_mode))
    {
        printf("socket\r\n");
    }


    close(fd);
    return 0;


}