/* Lucas Voron
 * May 30, 2021
 * COEN 12L
 * Project 5 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pqueue.h"

//Functions used to store priority queue in array
#define START 10
#define p(x) (((x)-1)/2)
#define l(x) (((x)*2)+1)
#define r(x) (((x)*2)+2)

typedef struct pqueue 
{
	int count;
	int length;
	void **data;
	int (*compare) ();
}PQ;

//Uses comparison function to return a pointer to a new priority queue
//Big-O O(1)
PQ *createQueue(int (*compare)())
{
	PQ *pq = malloc(sizeof(PQ));
	assert(pq != NULL);

	pq->count = 0;
	pq->length = START;
	pq->compare = compare;
	assert(compare != NULL);
	pq->data = malloc(sizeof(void*)*START);
	return pq;
}

//Frees memory pointed by pq in order to destroy the entire queue
//Big-O O(n)
void destroyQueue(PQ *pq)
{
	assert(pq != NULL);

 	free(pq->data);
	free(pq);
}

//Returns the number of elements in the priority queue using the count
//Big-O O(1)
int numEntries(PQ *pq)
{
	assert(pq != NULL);

    	return pq->count;
}

//Adds a new entry into the priority queue, but if the queue is full, another array that is double the length of the current one will be allocated and the old array will be copied over.  Then the old array will be deleted.
//Big-O O(log(n))
void addEntry(PQ *pq, void *entry)
{
	assert(pq != NULL && entry != NULL);

  	if(pq->length == pq->count)
    	{
      	pq->data = realloc(pq->data, sizeof(void *)*pq->length*2);
      	pq->length *= 2;
 	}
			    	
	pq->data[pq->count] = entry;
	int loc = pq->count; 

	while(pq->compare(pq->data[loc], pq->data[p(loc)]) < 0)
	{
	   	void *temp = pq->data[p(loc)];
        	pq->data[p(loc)] = pq->data[loc]; 
		pq->data[loc] = temp;
	}
  	pq->count++;
}

//Deletes and returns the smallest entry from the priority queue and shifts the elements in the array
//Big-O O(log(n))
void *removeEntry(PQ *pq)
{
	assert(pq != NULL);

    	void *root = pq->data[0];
    	int loc, small;
	loc = 0;
	small = 0; 
  	pq->data[loc] = pq->data[pq->count - 1];
 	pq->count--;

    	while(l(loc) < pq->count)
    	{
		small = l(loc);

		if(r(loc) < pq->count)
		{
			if(pq->compare(pq->data[l(loc)] , pq->data[r(loc)]) < 0)
				small = l(loc); 
			else 
				small = r(loc); 
		}
		
		if(pq->compare(pq->data[small],pq->data[loc]) < 0)
		{
			void *temp = pq->data[small]; 
			pq->data[small] = pq->data[loc];
			pq->data[loc] = temp; 
			loc = small; 
		}
		else
			break;
	} 
	return root; 
}
