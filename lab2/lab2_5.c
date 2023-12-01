/*
    Name: Kayleigh Vu
    Date: 09/28/2023
    Title: Lab2 – step 5
    Description: This program computes 4 processes which requires
    3 fork() system calls and each process will iterate a different
    delay taken as a commmand line argument from the user.
*/

/* C program to demonstrate the use of fork()*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */

/* main function */
int main(int argc, char *argv[]) {
    pid_t pid1, pid2;
    int i, n1, n2, n3, n4;
    n1 = atoi(argv[1]); // n is a delay in microseconds inserted in parent and child iterations
    n2 = atoi(argv[2]);
    n3 = atoi(argv[3]);
    n4 = atoi(argv[4]);

    if (argc < 4){  // to check that the user inputted less than needed commands
        printf ("Usage: %s <delay> \n",argv[0]);
        exit(0);
    }
    
    printf("\n Before forking.\n");
    pid1 = fork();
    if (pid1 < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }

    pid2 = fork();
    if (pid2 < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }

    if (pid1 > 0){

        if (pid2 > 0){ 
            // pid1 > 0 and pid2 > 0 (parent process)
            for (i=0;i<10;i++) {
                printf("This is the parent process pid=%d, the parent process is ppid=%d\n",getpid(), getppid());
                usleep(n1);
            }
        }
        else{
            // pid1 > 0 and pid2 == 0 (child process)
            for (i=0;i<10;i++) {
                printf("This is the c2 process pid=%d, the parent process is ppid=%d\n",getpid(), getppid());    
                usleep(n2);
            }
        }
    }

    else{
        if (pid2 > 0){ 
            // pid1 = 0 and pid2 > 0 (parent process)
            for (i=0;i<10;i++) {
                printf("This is the c1 process pid=%d, the parent process is ppid=%d\n",getpid(), getppid());
                usleep(n3);
            }
        }
        else{
            // pid1 = 0 and pid2 = 0 (child process)
            for (i=0;i<10;i++) {
                printf("This is the c3 process pid=%d, the parent process is ppid=%d\n",getpid(), getppid());    
                usleep(n4);
            }
        }
    }

    return 0;
}

