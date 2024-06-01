#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 

int main(void) 
{ 
    /* Create Child */ 
    switch (fork()) 
    { 
        case -1: 
            perror("fork error"); 
            exit(-1); 
        case 0:
            /* Child */ 
            printf("Child<%d>be created, Parent<%d>\n", getpid(), getppid()); 
            sleep(3);   

            //sleep 3 sec Wait for Parent Over 
            printf("Parent Proc<%d>\n", getppid());//Get Parent PID again
            _exit(0); 
        default: 
            /* Parent Proc */ 
            break; 
    } 

    sleep(1);
    printf("Parent_Proc Over!\n"); 
    exit(0); 
} 