/*
    Name: Kayleigh Vu
    Date: 09/28/2023
    Title: Lab2 – step 8
    Description: This program computes similarly to step 1 except that it uses threads
    instead of processes. When the child process is run (meaning the process ID is 0) 
    then it will read the ls of whatever folder the program is in.  The parent will wait 
    for the child to be finished/terminated for it to continue.
*/

/* C program to demonstrate the use of fork()*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
#include <pthread.h>    /* pthread */

void *parThread(void *arg){
    //parent thread
    int n = *((int *)arg);
    int i;
    for (i=0;i<10;i++) {
        printf("\t \t \t I am the parent Process displaying iteration %d \n",i);
        usleep(n);
    }
    pthread_exit(NULL);
}

void *chiThread(void *arg){
    //child thread
    int n = *((int *)arg);
    int i;
    for (i=0;i<10;i++) {
        printf("I am the child process displaying iteration %d\n",i);
        usleep(n);
    }
    pthread_exit(NULL);
}

/* main function */
int main(int argc, char *argv[]) {
    pid_t pid;
    pthread_t parentThread, childThread;
    int thread, n = atoi(argv[1]);

    //creating parent thread
    pthread_create(&parentThread, NULL, parThread, (void *) &n);

    //creating child thread
    pthread_create(&childThread, NULL, chiThread, (void *) &n);

    pthread_join(parentThread,NULL);
    pthread_join(childThread,NULL);

    return 0;
}