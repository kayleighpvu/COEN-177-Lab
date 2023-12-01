/*  
    Name: Kayleigh Vu
    Date: 11/16/2023
    Title: Lab8 – Step 5
    Description: This program computes similarly to step 4 with the reading and writing of the file but
    additionall in this program, we are creating multiple copies of the original/old file using threads
    of varying sizes which will be tested (2, 8, 32, and 64)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

int BUFFERSIZE;
int NTHREADS;
char oldfile[20];

void *go(void *arg){ 
    char buffer[BUFFERSIZE];    //create buffer with given buffersize
    char newfile[20];
    sprintf(newfile, "output%d.txt", (size_t) arg);
    FILE *fp, *fp2;             //create file pointers
    fp = fopen(oldfile, "rb");    //open the input file the user instructs
    fp2 = fopen(newfile, "wb");     //open the file to write into pointed with fp2
    while (fread(buffer, sizeof(buffer), 1, fp)){   //copy everything from file 1 to file 2 until either does not have enough space left or doesn't have any more contents to copy
        fwrite(buffer, sizeof(buffer), 1, fp2);
    }

    fclose(fp); //close file pointers
    fclose(fp2);
}

int main(int argc, char *argv[]){
    BUFFERSIZE = atoi(argv[2]);     //argument reads the buffer size
    NTHREADS = atoi(argv[3]);       //argument reads number of threads
    pthread_t threads[NTHREADS];    
    strcpy(oldfile, argv[1]);     //copy the argument from user to name of input file
    int i;

    for(i = 0; i < NTHREADS; i++){  //create threads--each reads and copies the file
	    pthread_create(&threads[i], NULL, go, (void *)(size_t) i);
    }

    for(i = 0; i < NTHREADS; i++){  //join threads
	    pthread_join(threads[i], NULL);
    }	    
    return 0;
}