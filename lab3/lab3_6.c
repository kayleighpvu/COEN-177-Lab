/*  Name: Kayleigh Vu
    Date: 10/05/2023
    Title: Lab3 – Inter-Process Communication and Pthreads – Step 6
    Description: This program computes similarly to lab 5 with producer and consumer
    except this program has producer and consumer communicate via shared memory rather
    than a pipe.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

//main
int main(int argc, char *argv[]) {
    char buff[1024];
    key_t key = 1111;
    int count, i;

    /*child 1 aka producer: calls producer function passing the pointer to the shared memory */
    if (fork() == 0) {
        int id = shmget(key, sizeof(char*), IPC_CREAT | 0666);
        for (i = 0; i < argc; i++) {
            strcat(strcat(buff, " "), argv[i]);
        }

        char *storage = (char *) shmat(id, 0, 0);
        strncpy(storage, buff, strlen(buff));
        shmdt(storage);
        exit(0);
        printf("\n");
    }

    /*child 2 aka consumer: calls consumer function passing the pointer to the shared memory */
    else if (fork() == 0) {
        int shmid = shmget(key, sizeof(char*), 0);
        char *storage = (char *)shmat(shmid, (void *)0, 0);
        while (strlen(storage) == 0) {
            sleep(1);
        }
        printf("%s\n", storage);

        shmdt(storage);
        shmctl(shmid, IPC_RMID, NULL);
    }

    else { /*parent closes both ends and wait for children*/
        wait(0);
        wait(0);

    }
    return 0;
}