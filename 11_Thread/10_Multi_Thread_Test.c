#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static void * new_thread(void * arg)
{
    int number = *((int *)arg);
    unsigned long int tid = pthread_self();
    printf("Current %d Thread, ThreadID = %ld\n", number, tid);
    return (void *)0;
}

static int nums[5] = {0, 1, 2, 3, 4};

int main (int argc, char *argv[])
{
    pthread_t tid[5];
    int j = 0;

    /* Created 5 Threads */
    for(j = 0;j < 5;j++)
    {
        pthread_create(&tid[j], NULL, new_thread, &nums[j]);
    }

    /* Wait For Thread End */
    for(int i = 0;i < 5;i++)
    {
        pthread_join(tid[i], NULL);
    }

    exit(0);
}















