/* Lucas Voron
 * May 2, 2021
 * COEN 12L
 * Project 3 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "set.h"
# include <stdbool.h>
# include <assert.h>

#define EMPTY 1
#define FILLED 2
#define DELETED 3

unsigned strhash(char *s);
static int search(SET *sp, char *elt, bool *found);

typedef struct set
{
	int count;
	int length;
	char ** data;
	int *flags;
} SET;

//Allocates memory for sets and creates them
//Big-O: O(n)
SET *createSet(int maxElts)
{
	int i;
	SET *sp;
	sp = (SET*)malloc(sizeof(SET));
	assert(sp != NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->data = (char **)malloc(sizeof(char*)*maxElts);
	assert(sp->data != NULL);
	sp->flags = malloc(sizeof(int*)*maxElts);
	assert(sp->flags != NULL);
	
	for(i = 0; i < sp->length; i++)
	{
		sp->flags[i] = EMPTY;
	}
	return sp;
}

//Deletes and frees the sets
//Big-O: O(n)
void destroySet(SET *sp)
{
	assert(sp != NULL);
	int i;
	
	for(i = 0; i < sp->count; i++)
	{
		if(sp->flags[i] == FILLED)
			free(sp->data[i]);
	}
	free(sp->data);
	free(sp->flags);
	free(sp);
	return;
}

//returns number of elements by returning count variable
//Big-O: O(1) 
int numElements(SET *sp)
{
	assert(sp != NULL);
	return (sp->count);
}

//Hashes elements to find them and inserts a new element in the correct spot
//Big-O: O(n)
void addElement(SET *sp, char *elt)
{
	assert(sp != NULL && elt != NULL);

	if (sp->count == sp->length) 
		return;

	bool found = false;
	int index = search(sp, elt, &found);
	
	if(found == true || index == -1) 
		return;
	
	sp->data[index] = strdup(elt);
	sp->flags[index] = FILLED;
	sp->count++;
	return;
}

//Hashes elements and removes element while freeing up memory
//Big-O: O(n)
void removeElement(SET *sp, char *elt)
{
	assert(sp != NULL && elt != NULL);
	bool found = false;
	int index = search(sp, elt, &found);
	if (found == true)
	{
		free(sp->data[index]);
		sp->flags[index] = DELETED;
		sp->count--;
	}
	return;
}

//Finds the element and returns the pointer with the index of that element
//Big-O: O(n)
char *findElement(SET *sp, char *elt)
{
	assert(sp != NULL && elt != NULL);
	bool found = false;
	int index = search(sp, elt, &found);
	
	if(found == true)
		return (sp->data[index]);
	return NULL;
}

//Allocates memory and copies char** data and returns the copy
//Big-O: O(n)
char **getElements(SET *sp)
{
	assert(sp != NULL);
	char ** copy = malloc(sizeof(char *)* sp->count);
	assert(copy != NULL);
	int i;
	int j = 0;
	
	for(i = 0; i < sp->length; i++)
	{
		if(sp->flags[i] == FILLED)
		{
			copy[j] = strdup(sp->data[i]);
			j++;
		}
	}
	return copy; 
}

//Hashes char * and reutrns the hash variable
//Big-O: O(1)
unsigned strhash(char *s)
{
	unsigned hash = 0;
	while(*s != '\0')
		hash = 31 * hash + *s ++;
	return hash;
}

//Hash searches for element and returns the index value
//Big-O: O(n)
static int search(SET *sp, char *elt, bool *found)
{
	assert(sp != NULL);
	assert(elt != NULL);
	int i, pos;
	int first = -1;
	*found = false;
	unsigned key = strhash(elt);

	for(i = 0; i < sp->length; i++)
	{
		pos = (key + i) % (sp->length);
		if(sp->flags[pos] == FILLED)
		{
			if(strcmp(elt, sp->data[pos]) == 0)
			{
				*found = true;
				return (pos);
			}
		}
		if(sp->flags[pos] == DELETED)
		{
			first = pos;
		}
		if(sp->flags[pos] == EMPTY)
		{
			if(first > -1)
			{
				return first;
			}
		return pos;
		}
	}
	return -1;
}
