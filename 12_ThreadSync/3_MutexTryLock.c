#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

static pthread_mutex_t mutex;
static int g_count = 0;


static void * new_thread_start(void * arg)
{
    int loops = *((int *)arg);
    int count_1 = 0;

    for(int j = 0;j < loops;j++)
    {
        while(pthread_mutex_trylock(&mutex));     /* Mutex Locked */

        count_1 = g_count;
        count_1++;
        g_count = count_1;

        pthread_mutex_unlock(&mutex);   /* Unlocked Mutex when Data Write OK */
    }
    return (void *)0;
}


static int loops;


int main (int argc, char *argv[])
{
    pthread_t tid1, tid2;
    int ret = 0;

    /* Get The User Parameter */
    if(argc < 2) loops = 10000000;
    else loops = atoi(argv[1]);

    /* Initial Mutex Lock */
    pthread_mutex_init(&mutex, NULL);

    /* Create 2　Thread */
    ret = pthread_create(&tid1, NULL, new_thread_start, &loops);
    if(ret)
    {
        fprintf(stderr, "Pthread Create Error: %s\n", strerror(ret));
        exit(-1);
    }

    ret = pthread_create(&tid2, NULL, new_thread_start, &loops);
    if(ret)
    {
        fprintf(stderr, "Pthread Create Error: %s\n", strerror(ret));
        exit(-1);
    }

    /* Wait Thread Run End */
    ret = pthread_join(tid1, NULL);
    if(ret)
    {
        fprintf(stderr, "Pthread_join Error: %s\n", strerror(ret));
        exit(-1);
    }
    ret = pthread_join(tid2, NULL);
    if(ret)
    {
        fprintf(stderr, "Pthread_join Error: %s\n", strerror(ret));
        exit(-1);
    }

    printf("g_count = %d\n", g_count);
    return 0;
}