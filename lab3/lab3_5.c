/*  Name: Kayleigh Vu
    Date: 10/05/2023
    Title: Lab3 – Inter-Process Communication and Pthreads – Step 5
    Description: This program computes pipes for the producer and consumer to communicate
    with each other.  The producer will write into the pipe and then the consumer will read
    what ever information producer put in from the other end.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

// producer which is located at the write end of pipe
void producer(FILE *pwrite) {
    int i;
    for (i = 0; i < 10; i++) {
        fprintf(pwrite, "%d", i);
        printf("producer: %d\n", i);
    }
    fclose(pwrite);
    exit(0);
}

// consumer which is located at the read end of pipe
void consumer(FILE *pread) {
    int input, i;
    while(1){
        int input = fscanf(pread, "%d", &i);
        if (input == 1)
            printf("consumer: %d\n", i);
        else break;
    }
    fclose(pread);
    exit(0);
}

//main
int main() {
    int fds[2];
    FILE *write, *read;
    int i;

    pipe(fds);
    read = fdopen(fds[0], "r");
    write = fdopen(fds[1], "w");

    /*child 1 aka producer: upstream (write) end of pipe */
    if (fork() == 0) {
        close(fds[0]);
        producer(write);
    }

    /*child 2 aka consumer: downstream (read) end of pipe */
    else if (fork() == 0) {
        close(fds[1]);
        consumer(read);
    }

    else { /*parent closes both ends and wait for children*/
        fclose(read);
        fclose(write);
        wait(0);
        wait(0);
    }
    return 0;
}