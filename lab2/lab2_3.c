/*
    Name: Kayleigh Vu
    Date: 09/28/2023
    Title: Lab2 – step 3
    Description: This program computes similarly to step 1 but the user will input
    via a command of the suspend delay for the parent and child process.
*/

/* C program to demonstrate the use of fork()*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */

/* main function */
int main(int argc, char *argv[]) {
    pid_t pid;
    int i, n;
    n = atoi(argv[1]); // n is a delay in microseconds inserted in parent and child iterations
    
    if (argc < 2){  // to check that the user inputted less than needed commands
        printf ("Usage: %s <delay> \n",argv[0]);
        exit(0);
    }
    
    printf("\n Before forking.\n");
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    exit(0);
    }

    if (pid){
        // Parent process: pid is > 0
        for (i=0;i<10;i++) {
            printf("\t \t \t I am the parent Process displaying iteration %d \n",i);
            usleep(n);
        }
    }

    else{
        // Child process: pid = 0
        for (i=0;i<10;i++) {
            printf("I am the child process displaying iteration %d\n",i);
            usleep(n);
        }
    }
    return 0;
}