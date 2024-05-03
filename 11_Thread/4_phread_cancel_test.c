#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

static void * new_thread_start(void * arg)
{
    printf("New Threa--Running\n");
    while(1)
    {
        sleep(2);
    }
    return(void *)0;
}

int main (void)
{
    pthread_t tid;
    int ret = 0;
    void * tret;

    ret = pthread_create(&tid, NULL, new_thread_start, NULL);
    if(ret)
    {
        printf(stderr, "Error %s\n", strerror(ret));
        exit(-1);
    }
    sleep(1);

    /* Terminated the thread */
    ret = pthread_cancel(tid);
    if(ret)
    {
        printf(stderr, "pthread_cancel Error %s\n", strerror(ret));
        exit(-1);
    }

    ret = pthread_join(tid, &tret);
    if(ret)
    {
        printf(stderr, "pthread_join Error %s\n", strerror(ret));
        exit(-1);
    }

    printf("New Thread End ,code = %ld\n", (long)tret);

    exit(0);
}