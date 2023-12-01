/*  Name: Kayleigh Vu
    Date: 11/09/2023
    Title: Lab 7 – LRU
    Description: This program (least recently used) starts off the same as FIFO where if there are open slots in queue then we put the page in there
    but with LRU, the new page will replace the page that has been used the least recently used page.  We search from where we last inserted the page + 1.
    We can keep track of oldest page and it's position in queue to know where the replacement can happen.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


typedef struct {//to 
    int pageno;
    int index;
} ref_page;


int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file

    int i,j;
    int totalFaults = 0; // keeps track of the total page faults
    int oldest;
    int oldestPos;
    int placeInArray = 0;
    int totalRequests = 0;

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        totalRequests++;

        for (i = 0; i < C_SIZE; i++)    //incrementing thru cache
        {
            oldest = cache[i].index;    //initialize oldest index
            if (cache[i].pageno == page_num)    //if already in cache
            {
                for (j = 0; j < C_SIZE; j++)    //increment index of items
                {
                    if (cache[j].index < cache[i].index)
                        cache[j].index++;
                }
                cache[i].index = 0;     //resetting index of i
                break;
            }
            else if (i == C_SIZE - 1) 	//if full array and page_num is not in array
            {
                totalFaults++;      //incrementing # of faults
                printf("%d\n",page_num);
                for (j = 0; j < C_SIZE; j++)    //increment index of items
                {
                    cache[j].index++;
                }
                for (j = 0; j < C_SIZE; j++)
                {
                    if (cache[j].index > oldest)    //an item older than current oldest is found
                    {
                        oldestPos = j; 				//position of oldest item
                        oldest = cache[j].index; 	//marking new oldest
                    }
                }
                cache[oldestPos].pageno = page_num;     //replace the oldest
                cache[oldestPos].index = 0;     //resetting index of oldest item
            }
        }
    }
    
    double hitRate = ((totalRequests - totalFaults) / (double) totalRequests);
    //double missRate = ((totalRequests - totalFaults) / (double) totalFaults); 
    printf("%d Total Page Requests\n", totalRequests);
    printf("%d Total Page Faults\n", totalFaults);
    printf("%.2f Hit Rate\n", hitRate);

    return 0;
}