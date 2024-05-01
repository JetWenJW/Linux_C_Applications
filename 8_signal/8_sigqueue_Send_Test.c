#include <stdio.h> 
#include <stdlib.h> 
#include <signal.h> 
 
int main(int argc, char *argv[]) 
{ 
    union sigval sig_val; 
    int pid; 
    int sig; 
 
    if (3 > argc) 
    {
        return 1;
    }
 
    /* Get The parameter */ 
    pid = atoi(argv[1]); 
    sig = atoi(argv[2]); 
    printf("pid: %d\n signal: %d\n", pid, sig); 
 
    /* Send SIG */ 
    sig_val.sival_int = 10; //Related Data
    if (0 < sigqueue(pid, sig, sig_val)) 
    { 
        perror("sigqueue error"); 
        return 1;
    } 
 
    puts("Send SIG Succeed!"); 
    return 0;
} 