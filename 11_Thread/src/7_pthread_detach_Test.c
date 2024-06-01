#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

static void * new_thread_start(void * arg)
{
    int ret = 0;

    /* Thread detach itself */
    ret = pthread_detach(pthread_self());
    if(ret)
    {
        printf(stderr, "pthread_detach Erorr%s\n", strerror(ret));
        return NULL;
    }

    printf("New Thread Start\n");
    sleep(2);       /* Sleep 2 seconds*/
    
    printf("New Thread End\n");
    pthread_exit(NULL);
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

    ret = pthread_join(tid, &tret);
    if(ret)
    {
        printf(stderr, "pthread_join Error %s\n", strerror(ret));
        exit(-1);
    }

    pthread_exit(NULL);
}