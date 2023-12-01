/*  Name: Kayleigh Vu
    Date: 11/09/2023
    Title: Lab 7 – Second Chance
    Description: This program is a combination of FIFO and second chance, meaning that
    pages are put into queue in a FIFO order and every page will be given a second chance.
    The second chance is so that the old page (that could be in use) is not replaced with a new page
    so that it doesn't have to stop its process.  We will keep track if a page is given a second chance or not
    using a reference bit 0 or 1.  There will also be a counter which will keep track of the reference bit.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct {//to 
    int pageno;
    int chance;
} ref_page;


int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file

    int i, j;
    int totalFaults = 0; // keeps track of the total page faults
    int counter = 0;
    int totalRequests = 0;
    
    for (i = 0; i < C_SIZE; i++){//initialise cache array  
        cache[i].pageno = -1;
        cache[i].chance = 0;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        totalRequests++;

        for (i = 0; i < C_SIZE; i++)
        {
            if (cache[i].pageno == page_num)
            {
                if (cache[i].chance == 0)    // setting chance to 1
                    cache[i].chance = 1;
                break;
            }
            else if (i == C_SIZE - 1)    //checking if page_num is in cache or not
            {
                totalFaults++; 	
                printf("%d\n",page_num);
                for (j = counter; j < C_SIZE; j++)
                {
                    if (cache[j].chance == 1)
                    {
                        cache[j].chance = 0;    //reset chance because if j already got 2nd chance (if chance is 1)
                        counter++; 				
                        if (counter == C_SIZE) 	//check if counter reaches the end
                        {
                            counter = 0; 			
                            j = -1; 			
                        }
                    }
                    else    //no second chance
                    {
                        cache[j].pageno = page_num; //replacing pageno
                        cache[j].chance = 0; 	//resetting the chance
                        counter++;
                        if (counter == C_SIZE)
                            counter = 0;
                        break;
                    }
                }
            }
        }
    }
    
    double hitRate = ((totalRequests - totalFaults) / (double) totalRequests);
    printf("%d Total Page Requests\n", totalRequests);
    printf("%d Total Page Faults\n", totalFaults);
    printf("%.2f Hit Rate\n", hitRate);

    return 0;
}