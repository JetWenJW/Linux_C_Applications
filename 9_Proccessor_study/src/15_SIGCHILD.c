#include <stdio.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
 
static void wait_child(int sig) 
{ 
    /* clear resource of Child-Processor */ 
    printf("Parent clear Child\n"); 
    while (waitpid(-1, NULL, WNOHANG) > 0) 
    {
        continue; 
    }
} 
 
int main(void) 
{ 
    struct sigaction sig = {0}; 
 
    /* SIGCHILD -> SIG_Handler */ 
    sigemptyset(&sig.sa_mask); 
    sig.sa_handler = wait_child; 
    sig.sa_flags = 0; 
    if (-1 == sigaction(SIGCHLD, &sig, NULL)) 
    { 
        perror("sigaction error"); 
        exit(-1); 
    } 
 
    /* Create Child */ 
    switch (fork()) 
    { 
        case -1: 
            perror("fork error"); 
            exit(-1); 
    
        case 0: 
            /* Child */ 
            printf("Child <%d>be created\n", getpid()); 
            sleep(1); 
            printf("Child Over\n"); 
            _exit(0);

            default: 
                /* Parent */ 
                break; 
    } 

    while(1)
    {
        sleep(3);
    }

    return (0); 
}