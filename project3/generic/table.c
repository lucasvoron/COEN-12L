/* Lucas Voron
 * May 2, 2021
 * COEN 12L
 * Project3 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "set.h"
# include <stdbool.h>
# include <assert.h>

#define EMPTY 1
#define FILLED 2
#define DELETED 3

static int search(SET *sp, void *elt, bool *found);

typedef struct set
{
	int count;
	int length;
  	void ** data;
 	int *flags;
 	int (*compare) ();
  	unsigned (*hash) ();
} SET;

//Function initializes sets and then sets all flags EMPTY
//Big-O: O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
	int i;
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);
 	sp->count = 0;
	sp->length = maxElts;
	sp->data = (void **)malloc(sizeof(void*)*maxElts);
	assert(sp->data != NULL);
 	sp->flags = malloc(sizeof(int*)*maxElts);
	assert(sp->flags != NULL);

	for(i=0; i<sp->length; i++)
	{
		sp->flags[i] = EMPTY;
	}
	sp->compare = compare;
	sp->hash = hash;
	return sp;
}

//Function deletes sets by freeing from memory
//Big-O: O(1)
void destroySet(SET *sp)
{
	assert(sp != NULL);
	free(sp->data);
	free(sp->flags);
	free(sp);
	return;
}

//Function returns the number of elements
//Big-O: O(1)
int numElements(SET *sp)
{
	 assert(sp != NULL);
	 return (sp->count);
}

//Function adds all elements into the void** data
//Big-O: O(n)
void addElement(SET *sp, void *elt)
{
	assert(sp != NULL && elt != NULL);
	if (sp->count == sp->length) return;
   	bool found = false;
    	int index = search(sp, elt, &found);

 	if(found == true || index == -1) return;

	sp->data[index] = elt;
 	sp->flags[index] = FILLED;
	sp->count++;
	return;
}

//Function finds and removes elt from table
//Big-O: O(n)
void removeElement(SET *sp, void *elt)
{
	assert(sp != NULL && elt != NULL);
	bool found = false;
	int index = search(sp, elt, &found);
	if (found == true)
	{
		sp->flags[index] = DELETED;
	 	sp->count--;
 	}
	return;
}

//Finds elt and returns
//Big-O: O(n)
void *findElement(SET *sp, void *elt)
{
	assert(sp != NULL && elt != NULL);
	bool found = false;
  	int index = search(sp, elt, &found);

	if(found == true)
	 	return (sp->data[index]);
	return NULL;
}

//Allocates and copies void**data
//Big-O: O(n)
void *getElements(SET *sp)
{
	assert(sp != NULL);
 	void ** copy = malloc(sizeof(void *)* sp->count);
	assert(copy != NULL);
	int i;
	int j = 0;
	
	for(i = 0; i < sp->length; i++)
	{
	 	if(sp->flags[i] == FILLED)
		{
			copy[j] = sp->data[i];
			j++;
		}
	}
	return copy; 
}

//Function uses hash function to search and return index
//Big-O: O(n)
static int search(SET *sp, void *elt, bool *found)
{
	assert(sp != NULL);
	assert(elt != NULL);
	int i, pos;
	int first = -1;
	*found = false;
	unsigned key = sp->hash(elt);

	for(i = 0; i < sp->length; i++)
	{
		pos = (key + i) % (sp->length);

		if(sp->flags[pos] == FILLED)
		{
			if((*sp->compare) (elt, sp->data[pos]) == 0)
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
