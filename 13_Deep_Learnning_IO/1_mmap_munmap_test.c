#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>


int main (int argc, char * argv[])
{
    int srcfd, dstfd;
    void * srcaddr;
    void * dstaddr;
    int ret = 0;
    struct stat sbuf;

    if(argc != 3)
    {
        fprintf(stderr, "Uesage: %s <srcfile> <dstfile>\n", argv[0]);
        exit(-1);
    }

    /* Open Source file */
    srcfd = open(argv[1], O_RDONLY);
    if(srcfd == -1)
    {
        perror("open Error");
        exit(-1);
    }

    /* Open Destanate File  */
    dstfd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0664);
    if(dstfd == -1)
    {
        perror("open Error");
        ret = -1;
        goto out1;
    }

    /* Get The Size of Source file */
    fstat(srcfd, &sbuf);

    /* Get The Size of Destinated File */
    ftruncate(dstfd, sbuf.st_size);

    /* Memory Mapping Source file to Memory Space */
    srcaddr = mmap(NULL, sbuf.st_size, PROT_READ, MAP_SHARED, srcfd, 0);
    if(MAP_FAILED == srcaddr)
    {
        perror("mmap Error");
        ret = -1;
        goto out2;
    }

    /* Memory Mapping Destnated file to MEmory Space  */
    dstaddr = mmap(NULL, sbuf.st_size, PROT_WRITE, MAP_SHARED, dstfd, 0);
    if(MAP_FAILED == dstaddr)
    {
        perror("mmap Error");
        ret = -1;
        goto out3;
    }

    /* Copy Source file to Destianted File */
    memcpy(dstaddr, srcaddr, sbuf.st_size);

/* Clear Before exit Program */
out4:
    /* Unmap Destinated File Memory Mapping */
    munmap(dstaddr, sbuf.st_size);

out3:
    /* Unmap Source File Memory Mapping */
    munmap(srcaddr, sbuf.st_size);

out2:
    /* Close Destinated File */
    close(dstfd);

out1:
    /* Close Source File */
    close(srcfd);
    exit(ret);
}



















