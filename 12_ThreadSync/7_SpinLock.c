#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

static pthread_spinlock_t spin; /* Spinlock */
static int g_count = 0;

static void * new_thread_start(void * arg)
{
    int loops = *((int *)arg);
    int count_1 = 0;

    for(int i = 0;i < loops;i++)
    {
        pthread_spin_lock(&spin);       /* SpinLock Locked    */
        
        count_1 = g_count;
        count_1++;
        g_count = count_1;

        pthread_spin_unlock(&spin);     /* Spinlock Unlocked */
    }

    return (void *)0;
}

static int loops;

int main(int argc, char * argv[])
{
    pthread_t tid1, tid2;
    int ret = 0;

    if(argc < 2)    /* Get The Parameter From User */
    {
        loops = 10000000;
    }
    else
    {
        loops = atoi(argv[1]);
    }

    /* Initial Spin Lock s(Private) */
    pthread_spin_init(&spin, PTHREAD_PROCESS_PRIVATE);

    /* Create 2 New Thread */
    ret = pthread_create(&tid1, NULL, new_thread_start, &loops);
    if(ret)
    {
        fprintf(stderr, "pthread_create Error: %s\n", strerror(ret));
        exit(-1);
    }

    ret = pthread_create(&tid2, NULL, new_thread_start, &loops);
    if(ret)
    {
        fprintf(stderr, "pthread_create Error: %s\n", strerror(ret));
        exit(-1);
    }

    /* Wait Thread End */
    ret = pthread_join(tid1, NULL);
    if(ret)
    {
        fprintf(stderr, "pthread_join Error: %s\n", strerror(ret));
        exit(-1);
    }

    ret = pthread_join(tid2, NULL);
    if(ret)
    {
        fprintf(stderr, "pthread_join Error: %s\n", strerror(ret));
        exit(-1);
    }

    /* Print Result */
    printf("g_count = %d\n", g_count);

    /* Destroy SpinLock */
    pthread_spin_destroy(&spin);
    return 0;
}