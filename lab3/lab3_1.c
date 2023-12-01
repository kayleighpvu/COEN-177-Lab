/*  Name: Kayleigh Vu
    Date: 10/05/2023
    Title: Lab3 – Inter-Process Communication and Pthreads – Step 1
    Description: This program computes an alphabetized list of all filenames of the current folder/directory when compiled/run
*/

/*Sample C program for Lab 3*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
//main
int main() {
    int fds[2];
    pipe(fds);
    /*child 1 duplicates downstream into stdin */
    if (fork() == 0) {
        dup2(fds[0], 0);
        close(fds[1]);
        execlp("more", "more", 0);
    }

    /*child 2 duplicates upstream into stdout */
    else if (fork() == 0) {
        dup2(fds[1], 1);
        close(fds[0]);
        execlp("ls", "ls", "-l", 0);
    }

    else { /*parent closes both ends and wait for children*/
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}

//fds[1]: write end of pipe (upstream)
//fds[0]: read end of pipe (downstream)