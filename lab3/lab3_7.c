
/*  Name: Kayleigh Vu
    Date: 10/05/2023
    Title: Lab3 – Inter-Process Communication and Pthreads – Step 7
    Description: This program computes the 10 threads but there is a bug when using i
    due to it being shared.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10

pthread_t threads[NTHREADS];
int main() {
    int i;
    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, &i);

    for (i = 0; i < NTHREADS; i++) {
        printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    }
    printf("Main thread done.\n");
    return 0;
}

void *go(void *arg) {
    printf("Hello from thread %d with iteration %d\n", (int)(unsigned long) pthread_self(), *(int *)arg);
    return 0;
}