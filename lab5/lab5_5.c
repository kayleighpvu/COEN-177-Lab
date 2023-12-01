/*  Name: Kayleigh Vu
    Date: 10/19/2023
    Title: Lab5 – Step 5
    Description: This program solves the producer-consumer problem similar to step 4 that used semaphores 
    but this program uses condition variables instead.  
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <signal.h>

#define NTHREADS 10
#define n 10

pthread_t threads[NTHREADS];
int in, out, count;
pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;
int buf[n];

//Producer thread
void *producer(void *arg){
    int item;
    do {
        item = rand() % 10;             //producting random item
        
        pthread_mutex_lock(&mutex);
        while (count == n){
            pthread_cond_wait(&empty, &mutex);
        }

        buf[in] = item;                 //add the item to buffer
        printf("Producer %d item: %d\n", (size_t) arg, item);

        in = (in + 1) % n;              //incrementing
        count++;                        //increasing count of items in buffer

        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    } while (1);

    pthread_exit(0);
}

//Consumer thread
void *consumer(void *arg){
    int item;
    do {
        pthread_mutex_lock(&mutex);

        while (count == 0){
            pthread_cond_wait(&full, &mutex);
        }
        
        item = buf[out];
        printf("Consumer %d item: %d\n", (size_t) arg, item);

        out = (out + 1) % n;
        count--;                        //decreasing count of items in buffer
        
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    } while (1);
    
    pthread_exit(0);
}

/*void cleanup(int sigtype){
    pthread_mutex_destroy("mutex");
    pthread_cond_destroy("empty");
    pthread_cond_destroy("full");

    printf("\n Terminating\n");
    exit(0);
}*/

int main() {
    int i;

    //initializing
    pthread_mutex_init(&mutex, NULL);              
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);  

    //using the first half # of threads for producers
    for (i = 0; i < NTHREADS/2; i++) {
        pthread_create (&threads[i], NULL, producer, (void *)(size_t)i);
    }

    //using the second half # of threads for consumers
    for (i = NTHREADS/2; i < NTHREADS; i++) {
        pthread_create (&threads[i], NULL, consumer, (void *)(size_t)i);
    }

    //join all the threads
    for(i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Main Thread Done\n");

    //destroying locks
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);

    return 0;
}