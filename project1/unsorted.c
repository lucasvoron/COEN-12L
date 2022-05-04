/* Lucas Voron
 * April 7, 2021
 * COEN 12L
 * Project 2 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include <assert.h>

static int search(SET *sp, char *elt);

typedef struct set //initializes structure with variables
{
	int length;
	int count;
	char **data;
}SET;

SET *createSet(int maxElts) //allocates memory and creates a set O(1)
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
	assert(sp != NULL);
	int i;

	for(i=0; i<sp->count; i++)
		free(sp->data[i]);
	free(sp->data);
	free(sp);
}

int numElements(SET *sp) //reports the number of elements by giving the count pointer O(1)
{
	return (sp->count);
}

void addElement(SET *sp, char *elt) //adds new element to the end of the array O(n)
{
	if(search(sp, elt) == -1)
	{
		if(sp->count == sp->length)
		{
			return;
		}
		sp ->data[sp->count] = strdup(elt);
		sp->count += 1;
	}
	return;
}

void removeElement(SET *sp, char *elt) //removes an element and moves last element to that empty slot O(n)
{
	assert(sp != NULL);
	assert(elt != NULL);
	int index = search(sp, elt);

	if(index == -1)
		return; 

	sp->data[index] = sp->data[sp->count-1];
	sp->data[sp->count-1] = NULL;
	sp->count -= 1;
	return;
}

char *findElement(SET *sp, char *elt) //returns the string by giving the data pointer O(n)
{
	int temp = search(sp, elt);

	if(temp != -1)
		return sp->data[temp];
	return NULL;
}

char **getElements(SET *sp) //returns a copied version of the data pointer O(n)
{
	int i;
	char **copy = malloc(sizeof(sp->data));

	for(i = 0; i < sp->count; i++)
		copy[i] = sp->data[i];
	return copy;
}

static int search(SET *sp, char *elt) //searches through and returns the index of the element O(n)
{
	int i;

	for(i=0; i<sp->count; i++)
	{
		if(strcmp(elt, sp->data[i])==0)
			return i;
	}
	return -1;
}
