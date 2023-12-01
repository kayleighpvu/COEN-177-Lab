#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

 

void *go(void *);
#define NTHREADS 20
pthread_t threads[NTHREADS];

int main() {
    int i;

    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    printf("Main thread done.\n");

    return 0;
}

void *go(void *arg) {
    printf("Hello from thread %d with iteration %d\n",  (int)(unsigned long)pthread_self(), (int)(unsigned long)(size_t *)arg);
    sleep(15);
    pthread_exit(0);
}

/*
The function go() in the program in Step 1 has the parameter arg passed a local variable.

Is the variable per thread variable or a shared state?
per thread variable

Where does the compiler store the variable’s state?
thread's stack
*/

/*
The main() in the program in Step 1 has local variable i.
per thread variable

Where does the compiler store the variable’s state?
thread's stack
*/