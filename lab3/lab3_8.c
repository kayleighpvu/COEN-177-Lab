/*  Name: Kayleigh Vu
    Date: 10/05/2023
    Title: Lab3 – Inter-Process Communication and Pthreads – Step 8
    Description: This program computes part 7's program but fixes the bug by casting value
    of i when creating a thread.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10

pthread_t threads[NTHREADS];
int main() {
    int i;
    /*for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, &i);*/

    //need to pass the actual object of i and 
    //size_t for i to make object separately rather than using the shared i from main function
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);   

    for (i = 0; i < NTHREADS; i++) {
        printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    }
    printf("Main thread done.\n");
    return 0;
}

void *go(void *arg) {
    printf("Hello from thread %d with iteration %d\n", (int)(unsigned long) pthread_self(), (size_t)arg);
    return 0;
}