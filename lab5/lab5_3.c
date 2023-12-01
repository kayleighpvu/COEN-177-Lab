/*  Name: Kayleigh Vu
    Date: 10/19/2023
    Title: Lab5 – Step 3
    Description: This program computes similarly to threadSync program but this program will contain mutex 
    locks instead of semaphores to create, run, and complete the threads.  It is designed so that each thread 
    will get the lock, run its critical section, and release the lock (unlock the lock) which the next waiting
    thread will get until all 10 threads are completed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h> 
#include <unistd.h>


#define NTHREADS 10

void *go(void *arg);
//void cleanup(int sigtype);

pthread_t threads[NTHREADS];
//sem_t *mutex;
pthread_mutex_t lock;

int main() {
    //signal(SIGINT,cleanup);
    //mutex = sem_open("mutex", O_CREAT, 0644, 1);
    pthread_mutex_init(&lock, NULL);
    int i;
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    for (i = 0; i < NTHREADS; i++) 
        pthread_join(threads[i],NULL);
    //sem_unlink("mutex");
    printf("Main Thread Done\n");
    pthread_mutex_destroy(&lock);
    return 0;
}

void *go(void *arg) {
    printf("Thread %d is now attempting ....\n",  (int)(size_t)arg);
    pthread_mutex_lock(&lock);
    //sem_wait(mutex);
    sleep(1);
    printf("Thread %d is running in its Critical Section........\n",  (int)(size_t)arg);
    pthread_mutex_unlock(&lock);
    //sem_post(mutex);
    pthread_exit(0);
}

/*void cleanup(int sigtype){
    sem_unlink("mutex");
    printf("\n Terminating\n");
    exit(0);
}*/

