/*  Name: Kayleigh Vu
    Date: 10/19/2023
    Title: Lab5 – Step 4
    Description: This program solves the producer-consumer problem using semaphores.  The code has 10 threads
    where the first 5 are used for producer and the second 5 are used for the consumer.  The producer's 
    purpose is to generate a random item, put it into the buffer which then the consumer's purpose is to take 
    out that item from the buffer.
*/

//Shared data: semaphore full, empty, mutex;
//pool of n buffers, each can hold one item
//mutex provides mutual exclusion to the buffer pool
//empty and full count the number of empty and full buffers
//Initially: full = 0, empty = n, mutex = 1

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
int in, out;
sem_t *full;    //full = 0
sem_t *empty;   //empty = n
sem_t *mutex;   //mutex = 1
int buf[n];

//Producer thread
void *producer(void *arg){
    int item;
    do {
        item = rand() % 10;             //producting random item
        sem_wait(empty);
        sem_wait(mutex);

        buf[in] = item;                 //add the item to buffer
        printf("Producer %d item: %d\n", (size_t) arg, item);

        in = (in + 1) % n;              //incrementing
        
        sem_post(mutex);
        sem_post(full);
        sleep(1);
    } while (1);

    pthread_exit(0);
}

//Consumer thread
void *consumer(void *arg){
    int item;
    do {
        sem_wait(full);
        sem_wait(mutex);
        
        item = buf[out];
        printf("Consumer %d item: %d\n", (size_t) arg, item);

        out = (out + 1) % n;

        sem_post(mutex);
        sem_post(empty);
        sleep(1);
    } while (1);
    pthread_exit(0);
}

/*void cleanup(int sigtype){
    sem_unlink("mutex");
    sem_unlink("empty");
    sem_unlink("full");

    printf("\n Terminating\n");
    exit(0);
}*/

int main() {
    int i;
    in = 0;
    out = 0;

    sem_unlink("mutex2");
    sem_unlink("full2");
    sem_unlink("empty2");

    mutex = sem_open("mutex2", O_CREAT, 0644, 1);    //initial mutex = 1
    full = sem_open("full2", O_CREAT, 0644, 0);      //initial full = 0
    empty = sem_open("empty2", O_CREAT, 0644, n);    //initial empty = n

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
    return 0;
}