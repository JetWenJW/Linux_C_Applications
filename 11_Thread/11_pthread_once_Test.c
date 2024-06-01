#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


static pthread_once_t once = PTHREAD_ONCE_INIT;

static void initialize_once(void)
{
    printf("initialize_once Function run : Thread_ID : %ld\n", pthread_self());

}

static void func(void)
{
    pthread_once(&once, initialize_once);
    printf("initialize_once RUN OVER\n");
}

static void * thread_start(void * arg)
{
    printf("Thread %d be created : Thread_ID %ld\n", *((int *)arg), pthread_self());
    func();             /* Call the Function  */
    pthread_exit(NULL); /* Thread Run End */

}
 
static int nums[5] = {0, 1, 2, 3, 4}; 

int main (void)
{
    pthread_t tid[5];

    /* Created 5 Threads */
    for(int i = 0;i < 5;i++)
    {
        pthread_create(&tid[i], NULL, thread_start, &nums[i]);
    }

    /* Wait For Thread Run End */
    for(int i = 0;i < 5;i++)
    {
        pthread_join(tid[i], NULL);
    }

    exit(0);
}

