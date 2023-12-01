#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#define NTHREADS 2
void *go(void *arg);
pthread_t threads[NTHREADS];

struct d {
 int j;
 int turn;
 bool flag[2];
};

int main() {
 struct d *data = (struct d *) malloc (sizeof(struct d));
 data -> flag[0] = false;
 data -> flag[1] = false;
 int i;
 for (i = 0; i < NTHREADS; i++){
   data -> j = i; 
   pthread_create(&threads[i], NULL, go, data);
   sleep(1);
 }
 for (i = 0; i < NTHREADS; i++) 
   pthread_join(threads[i],NULL);
 return 0;
}

void *go(void *arg) {
 struct d *data = arg;
 int k = data -> j;
 data -> flag[k] = true; 
 data -> turn = !k; 
 //sleep(10);
 printf("Thread %d is now attempting ....\n", k);
 while (data -> flag[!k] && data -> turn == !k); 
 printf("Thread %d is running in its Critical Section........\n", k);
 data -> flag[k] = false;
 pthread_exit(0);
}