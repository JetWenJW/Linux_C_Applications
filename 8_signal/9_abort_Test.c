#include <stdio.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <unistd.h> 
 
static void sig_handler(int sig) 
{ 
    printf("Get the Sig: %d\n", sig); 
} 
 
int main(int argc, char *argv[]) 
{ 
    struct sigaction sig = {0}; 
 
    sig.sa_handler = sig_handler; 
    sig.sa_flags = 0; 
    
    if (-1 == sigaction(SIGABRT, &sig, NULL)) 
    { 
        perror("sigaction error"); 
        return 1;
    } 
 
    sleep(2); 
    abort();    // called abort 

    while(1)
    {
        sleep(1);
    }        
    
    return 0;
} 