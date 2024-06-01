#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <unistd.h> 
#include <string.h> 
 
static int g_count = 0; 
 
static void *new_thread_start(void *arg) 
{ 
    int loops = *((int *)arg); 
    int l_count, j; 
 
    for (j = 0; j < loops; j++) 
    { 
        l_count = g_count; 
        l_count++; 
        g_count = l_count; 
    } 
 
    return (void *)0; 
} 
 
static int loops; 
int main(int argc, char *argv[]) 
{ 
    pthread_t tid1, tid2; 
    int ret; 
 
    /* Get The Parameter */ 
    if (2 > argc) 
        loops = 10000000;   /* Default 10000000 times */ 
    else 
        loops = atoi(argv[1]); 
 
    /* Create 2 Thread */ 
    ret = pthread_create(&tid1, NULL, new_thread_start, &loops); 
    if (ret) 
    { 
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret)); 
        exit(-1); 
    } 
 
    ret = pthread_create(&tid2, NULL, new_thread_start, &loops);
     if (ret) { 
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret)); 
        exit(-1); 
    } 
 
    /* Wait Thread End */ 
    ret = pthread_join(tid1, NULL); 
    if (ret) { 
        fprintf(stderr, "pthread_join error: %s\n", strerror(ret)); 
        exit(-1); 
    } 
 
    ret = pthread_join(tid2, NULL); 
    if (ret) { 
        fprintf(stderr, "pthread_join error: %s\n", strerror(ret)); 
        exit(-1); 
    } 
 
    printf("g_count = %d\n", g_count); 
    exit(0); 
} 