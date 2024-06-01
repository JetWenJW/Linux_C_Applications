#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>


static pthread_mutex_t mutex;
static int g_avail = 0;

/* Consumer Thread */
static void * consumer_thread(void * arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);     /* Lock Mutex */
    
        while(g_avail > 0)
        {
            g_avail--;                  /* Consume */
        }
        pthread_mutex_unlock(&mutex);   /* Unlock */
    }
    return (void *)0;
} 

/* Producter Thread */
int main(int argc, char *argv[])
{
    pthread_t tid;
    int ret = 0;

    /* Initial Mutex */
    pthread_mutex_init(&mutex, NULL);

    /* Create New Thread ( Create Task )*/
    ret = pthread_create(&tid, NULL, consumer_thread, NULL);
    if(ret)
    {
        fprintf(stderr, "pthread_create Error: %s\n", strerror(ret));
        exit(-1);
    }

    while(1)
    {
        pthread_mutex_lock(&mutex);     /* Lock Mutex */
        g_avail++;                      /* Produce */
        pthread_mutex_unlock(&mutex);   /* Unlocked */
    }
    return 0;
}
