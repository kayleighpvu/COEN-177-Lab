/*  Name: Kayleigh Vu
    Date: 10/05/2023
    Title: Lab3 – Inter-Process Communication and Pthreads – Step 2
    Description: This program computes finding the number of arguments passed from 
    the user using the writer (upstream part of pipe) when compiling and then the 
    reader outputs the arguments it read from the writer and prints them back to user
*/

/*Sample C program for Lab 3*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// main
int main(int argc,char *argv[]){
    int  fds[2];
    char buff[60];
    int count;
    int i;
    pipe(fds);  

    if (fork()==0){
        printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
        close(fds[0]);
        for(i=0;i<argc;i++){
            write(fds[1],argv[i],strlen(argv[i]));
        }
        exit(0);
    }

    else if(fork()==0){
        printf("\nReader on the downstream end of the pipe \n");
        close(fds[1]);
        while((count=read(fds[0],buff,60))>0){
            for(i=0;i<count;i++){
                write(1,buff+i,1);
                write(1," ",1);
            }
            printf("\n");
        }
        exit(0);
    }

    else{     
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
return 0;

}
