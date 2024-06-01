#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <unistd.h> 
 
static void cleanup(void *arg) 
{ 
    printf("cleanup: %s\n", (char *)arg); 
} 
 
static void *new_thread_start(void *arg) 
{ 
    printf("New Thread--start run\n"); 
    pthread_cleanup_push(cleanup, "1 called"); 
    pthread_cleanup_push(cleanup, "2 called"); 
    pthread_cleanup_push(cleanup, "3 called"); 
 
    sleep(2); 
    pthread_exit((void *)0);    //Thread terminate 
 
    pthread_cleanup_pop(0); 
    pthread_cleanup_pop(0); 
    pthread_cleanup_pop(0); 
} 
 
int main(void) 
{ 
    pthread_t tid; 
    void *tret; 
    int ret; 
 
    /* Create New Thread */ 
    ret = pthread_create(&tid, NULL, new_thread_start, NULL); 
    if (ret) { 
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret)); 
        exit(-1); 
    } 
 
    /* Wait New Thread Terminate */ 
    ret = pthread_join(tid, &tret); 
    if (ret) { 
        fprintf(stderr, "pthread_join error: %s\n", strerror(ret)); 
        exit(-1); 
    } 
    printf("New thread End, code=%ld\n", (long)tret); 
 
    exit(0); 
} 