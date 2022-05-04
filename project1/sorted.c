/* Lucas Voron
 * April 14, 2021
 * COEN 12L
 * Project 2 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include <assert.h>
#include <stdbool.h>

static int search(SET *sp, char *elt, bool *found);

typedef struct set //initializes structure with variables O(n)
{
	int length;
	int count;
	char **data;
}SET;

SET *createSet(int maxElts) //allocates memory and creates a set O(n)
{
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);

	sp->count = 0;
	sp->length = maxElts;
	sp->data = malloc(sizeof(char*)*maxElts);

	assert(sp->data != NULL);
	return sp;
}

void destroySet(SET *sp) //frees each variable and the structure O(n)
{
	int i;
	assert(sp != NULL);

	for(i=0; i<sp->count; i++)
		free(sp-> data[i]);
	free(sp->data);
	free(sp);
	return;
}

int numElements(SET *sp) //returns the number of elements in array by giving the count pointer O(1)
{
	assert(sp != NULL);
	return (sp->count);
}

void addElement(SET *sp, char *elt) //adds new element to the sorted array O(n(logn))
{
	assert(sp != NULL);
	int i;
	bool found = true;
	int index = search(sp, elt, &found);

	if(found == true)
		return;

	if(sp->count == sp->length)
	{
		return;
	}

	for(i=sp->count; i>index; i--)
	{
		sp->data[i] = sp->data[i-1];
	}

	sp->data[index] = strdup(elt);
	sp->count += 1;
	return;
}

void removeElement(SET *sp, char *elt) //removes an element and shifts other elements O(n(logn))
{
	assert(sp != NULL);
	bool found = false;
	int i;
	int index = search(sp, elt, &found);

	if(found == true)
	{
		free(sp->data[index]);
		for(i=index+1; i<sp->count; i++)
		{
			sp->data[i-1] = sp->data[i];
		}
		sp->count -= 1;
	}
	return;
}

char *findElement(SET *sp, char *elt) //returns the string by giving the data pointer O(logn)
{
	assert(sp != NULL);
	bool found = true;
	int temp = search(sp, elt, &found);

	if(found == true)
		return sp->data[temp];
	return NULL;
}

char **getElements(SET *sp) //returns a copied version of the data pointer O(n)
{
	assert(sp != NULL);
	int i;
	char **copy = malloc(sizeof(char *)*sp->count);

	memcpy(copy, sp->data, sizeof(char *)*sp->count);
	return copy;
}

static int search(SET *sp, char *elt, bool *found) //binary search through and returns the index of the element O(logn)
{
	assert(sp != NULL);
	int mid;
	int low = 0;
	int high = sp->count - 1;
	
	while(low <= high)
	{
		mid = ((high + low) / 2);
										        
		if(strcmp(sp->data[mid], elt) > 0)
			high = mid - 1;
		if(strcmp(sp->data[mid], elt) < 0)
			low = mid + 1;
		if(strcmp(elt, sp->data[mid]) == 0)
		{
			*found = true;
			return mid;
		}
   	}
	*found = false;
	return low;
}
