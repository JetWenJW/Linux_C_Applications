#include <stdio.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <unistd.h> 
 
static void sig_handler(int sig, siginfo_t *info, void *context) 
{ 
    sigval_t sig_val = info->si_value; 
 
    printf("Recceive SIGNAL: %d\n", sig); 
    printf("Related Data: %d\n", sig_val.sival_int); 
} 
 
int main(int argc, char *argv[]) 
{ 
    struct sigaction sig = {0}; 
    int num; 
 
    if (2 > argc)
    {
        return 1;
    } 
 
    num = atoi(argv[1]); 
 
    sig.sa_sigaction = sig_handler; 
    sig.sa_flags = SA_SIGINFO; 
    if (-1 == sigaction(num, &sig, NULL)) 
    { 
        perror("sigaction error"); 
        return 1; 
    } 
 
    while(1)
    {
        sleep(1); 
    }
 
    return 0;
} 