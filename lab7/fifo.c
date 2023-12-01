/*  Name: Kayleigh Vu
    Date: 11/09/2023
    Title: Lab 7 – FIFO
    Description: This program is in first in-first out order which puts the page into the cache is it is not there already
    and as we go through more pages and there are no more open spots in queue to put new page, the new page then replaces
    the page that is first in the queue/the page that has been there the longest.  At the multiple replacements happen, the page
    that has been there the longest moves to the first slot in queue.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


typedef struct {//to 
    int pageno;
} ref_page;


int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file

    int i;
    int totalFaults = 0; // keeps track of the total page faults
    int placeInArray = 0;   // keeps the position in cache
    int totalRequests = 0; // keeps track of total requests made

    for (i = 0; i < C_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        bool foundInCache = false;  //check if found in cache or not

        for (i = 0; i < C_SIZE; i++) {  //loop thru cache array
            if (cache[i].pageno == page_num) { //if page found in cache
                foundInCache = true;    //set found to true
                break; //break out loop because found page_num in cache
            }
        }
        if (foundInCache == false){ //if not found in cache
            printf("%d\n",page_num);
            cache[placeInArray].pageno = page_num;  //putting page into cache
            totalFaults++;  //there was a fault so increment
            placeInArray++; //need to keep the value within the cacheSize

            if (placeInArray == C_SIZE)
                placeInArray = 0;
        }
        totalRequests++;
    }
    
    double hitRate = ((totalRequests - totalFaults) / (double) totalRequests); //calculate hit rate
    printf("%d Total Page Requests\n", totalRequests);  //print total # of requests
    printf("%d Total Page Faults\n", totalFaults);  //print total # of faults made (page not found in cache)
    printf("%.2f Hit rate\n", hitRate);   

    return 0;
}