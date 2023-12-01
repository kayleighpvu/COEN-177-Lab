/*  Name: Kayleigh Vu
    Date: 11/09/2023
    Title: Lab 7 – Step 2
    Description: This program reads the output of $cat testInput.txt (to print out contents of txt file) pipelined
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    char pageCache[100];
    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache);
        printf("%d\n", page_num);
    }

    return 0;



}
