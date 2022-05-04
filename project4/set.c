/* Lucas Voron
 * May 16, 2021
 * COEN 12L
 * Project 4 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "set.h"
#include "list.h" 
#define  AVG 20

typedef struct node
{
	void *data;
 	struct node *next;
 	struct node *prev; 
} NODE;

typedef struct list
{
	int count; 
	struct node *head; 
 	int (*compare) ();
} LIST;

typedef struct set 
{
	int length;
 	int count;
    	int (*compare)();
    	unsigned (*hash)();
    	LIST **lists; 
} SET;

//Creates the set of elements
//Big-O O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{    
	int i;
	SET *sp;    
	assert(compare != NULL && hash != NULL);    
	sp = malloc(sizeof(SET));    
	assert(sp != NULL); 
	sp->compare = compare;    
	sp->hash = hash;    
	sp->count = 0;   
	sp->length =  maxElts / AVG; 
	sp->lists = malloc(sizeof(LIST*)*sp->length);
												
	for(i = 0; i < sp->length; i++)
		sp->lists[i] = createList(compare);
	return sp;
}

//Frees and destroys the entire set
//Big-O O(1)
void destroySet(SET *sp)
{
  	free(sp->lists);
	free(sp);
}

//Returns the number of elements in the list
//Big-O O(1)
int numElements(SET *sp)
{
	assert(sp != NULL);
   	return sp->count;
}

//Adds a new element into the list
//Big-O O(n)
void addElement(SET *sp, void *elt)
{
	assert(sp != NULL && elt != NULL);
   	int index = (*sp->hash)(elt) % sp->length;

   	if(findItem(sp->lists[index],elt) == NULL)
	{
       	addFirst(sp->lists[index] , elt);
      	sp->count++;
	}
}

//Searches through list and deletes an element if it exists
//Big-O O(n)
void removeElement(SET *sp, void *elt)
{
	assert(sp != NULL && elt != NULL);
	int index = (*sp->hash)(elt)%sp->length;

	if(findItem(sp->lists[index],elt) != NULL)	
	{
		removeItem(sp->lists[index], elt);
	   	sp->count--;
   	}
}

//Finds an element in the list and returns its index
//Big-O O(n)
void *findElement(SET *sp, void *elt)
{
	assert(sp != NULL && elt != NULL);
   	int index = (*sp->hash)(elt) % sp->length;

	return findItem(sp->lists[index], elt); 
}

//Returns a copy of the elements data in the list
//Big-O O(n)
void *getElements(SET *sp)
{
	assert(sp != NULL);
  	//NODE *np;
   	void **copy = malloc(sizeof(void*)*sp->count);
   	int i, j, k;
    	j = 0; 
	k = 0;

	for(i = 0; i < sp->length; i++)
   	{
		int num = numItems(sp->lists[i]);
	    	if(num != 0)
      	{
			void **items = getItems(sp->lists[i]);

			memcpy(copy+k, items, sizeof(void *)*num);
		    	k+=num;
		}
	}
	return copy; 
}
