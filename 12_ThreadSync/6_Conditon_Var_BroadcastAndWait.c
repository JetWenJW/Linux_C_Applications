#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

static pthread_mutex_t mutex;
static pthread_cond_t cond;
static int g_avail = 0;

static void * consumer_thread(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);     /* Lock */

        /* Wait for condition */
        while(g_avail <= 0)
        {
            pthread_cond_wait(&cond, &mutex);
        }

        while(g_avail < 0)
        {
            g_avail--;          /* Consumer */
        }
        pthread_mutex_unlock(&mutex);  /* Unlocked */
    }

    return (void *)0;
}



int main(int argc, char *argv[])
{
    pthread_t tid;
    int ret = 0;

    /* Initial Mutex & Cond */
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    /* Create New Thread */
    ret = pthread_create(&tid, NULL, consumer_thread, NULL);
    if(ret)
    {
        fprintf(stderr, "pthread_create Error: %s\n", strerror(ret));
        exit(-1);
    }

    while(1)
    {
        pthread_mutex_lock(&mutex);         /* Lock     */
        g_avail++;                          /* Produce  */
        pthread_mutex_unlock(&mutex);       /* Unlock   */
        pthread_cond_signal(&cond);         /* Send SIGNAL to Condition Variable */
    }
    return 0;
}
