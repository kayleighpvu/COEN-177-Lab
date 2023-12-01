/*  Name: Kayleigh Vu
    Date: 11/09/2023
    Title: Lab 7 – Step 1
    Description: This program creates text files of adjustable sizes
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define someNumber 10000
#define capNumber 1000

int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer [sizeof(int)];
    int i;

    fp = fopen("testInput10k.txt", "w");       //generate & open a new txt file with file pointer fp
    
    for (i = 0; i < someNumber; i++){
        sprintf(buffer, "%d\n", rand() % capNumber);
        fputs(buffer, fp);      //write a string of characters into txt file pointed by fp
    }

    fclose(fp);     //close the testInput.txt file
    return 0;
}