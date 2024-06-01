#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>


static pthread_rwlock_t rwlock;/* Define  RWLock*/
static int g_count = 0;

static void * read_thread(void *arg)
{
    int number = *((int *)arg);
    
    for(int i = 0;i < 10;i++)
    {
        pthread_rwlock_rdlock(&rwlock);/* Lock Rwlock By Read Mode */
        printf("Read Thread<%d>, g_count = %d\n", number + 1, g_count);
        pthread_rwlock_unlock(&rwlock);/* Unlock */
        sleep(1);
    }
    return (void *)0;
}

static void * write_thread(void *arg)
{
    int number = *((int *)arg);
    
    for(int i = 0;i < 10;i++)
    {
        pthread_rwlock_wrlock(&rwlock);/* Lock Rwlock By Write Mode */
        printf("Write Thread<%d>, g_count = %d\n", number + 1, g_count += 20);
        pthread_rwlock_unlock(&rwlock);/* Unlock */
        sleep(1);
    }
    return (void *)0;
}

static int nums[5] = {0, 1, 2, 3, 4};

int main(int argc, char *argv[])
{
    pthread_t tid[10];

    /* Initial RWLock */
    pthread_rwlock_init(&rwlock, NULL);

    /* Create 5 Thread that Read g_count Variable */
    for( int i = 0;i < 5;i++)
    {
        pthread_create(tid[i], NULL, read_thread, &nums[i]);
    }

    /* Create 5 Thread that Write g_count Variable */
    for( int i = 0;i < 5;i++)
    {
        pthread_create(tid[i+5], NULL, write_thread, &nums[i]);
    }

    /* Wait All Thread Run End */
    for( int i = 0;i < 10;i++)
    {
        pthread_join(tid[i], NULL);
    }

    /* Destroy RWLock*/
    pthread_rwlock_destroy(&rwlock);
    return 0;
}




