#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

static void * new_thread_start(void * arg)
{
    printf("New Thread : Processor ID = %d, Thread ID = %ld", getpid(), pthread_self());
    return (void *)0;
}

int main (void)
{
    pthread_t tid;
    int ret = 0;
    ret = pthread_create(&tid, NULL, new_thread_start, NULL);
    if(ret)
    {
        printf(stderr, "Error %s\n", strerror(ret));
        exit(-1);
    }

    printf("Main Thread: Proccessor ID = %d, Thread ID = %ld\n", getpid(), pthread_self());
    sleep(1);
    exit(0);
}