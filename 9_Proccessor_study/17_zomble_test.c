#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
 
int main(void) 
{ 
    /* Craete Child Proc */ 
    switch (fork()) { 
    case -1: 
        perror("fork error"); 
        exit(-1); 
 
    case 0: 
        /* Child Proc */ 
        printf("child<%d>be created\n", getpid()); 
        sleep(1); 
        printf("Child_Proc Over\n"); 
        _exit(0); 
 
    default: 
        /* Parent_proc */ 
        break; 
    } 
 
    while(1)
    {
        sleep(1); 
    }        
 
    return 0;
}