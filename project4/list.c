/* Lucas Voron
 * May 16, 2021
 * COEN 12L
 * Project 4 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

struct list
{
	int count;   
	struct node *head;
	int (*compare)();
};

typedef struct list LIST;

struct node
{
	void *data;     
	struct node *next;   
	struct node *prev;
};

typedef struct node NODE;

//Creates the list
//Big-O O(1)
LIST *createList(int (*compare) ())
{
	LIST *lp = malloc(sizeof(LIST));
	assert(lp != NULL);
	lp->count = 0;
	lp->compare = compare;
	lp->head = malloc(sizeof(NODE));
	assert(lp->head != NULL);
	lp->head->next = lp->head;    
	lp->head->prev = lp->head;    
	return lp;
}

//Frees and destroys the entire list
//Big-O O(n)
void destroyList(LIST *lp)
{
	assert(lp != NULL);
	NODE *pDel, *pNext;
	pDel = lp->head;

	do
	{
		pNext = pDel->next;
		free(pDel);
		pDel = pNext;
	} while (pDel != lp->head);
	
	free(lp);
}

//Returns the number of elements in the list
//Big-O O(1)
int numItems(LIST *lp)
{
	assert(lp != NULL);
	return (lp->count);
}

//Adds a new element to the begining of the list
//Big-O O(1)
void addFirst(LIST *lp, void *item)
{
	assert(lp != NULL && item != NULL);
	NODE *temp = malloc(sizeof(NODE));

	temp->data = item;
	temp->prev = lp->head;
	temp->next = lp->head->next;
	lp->head->next = temp;
	temp->next->prev = temp;
	lp->count++;
}

//Adds a new element to the end of the list
//Big-O O(1)
void addLast(LIST *lp, void *item)
{
	assert(lp != NULL && item != NULL);
	NODE *temp = malloc(sizeof(NODE));

	temp->data = item; 
	temp->next = lp->head;
	temp->prev = lp->head->prev;
	lp->head->prev = temp;
	temp->prev->next = temp;
	lp->count++;
}

//Removes the first element of the list
//Big-O O(1)
void *removeFirst(LIST *lp)
{
	assert(lp != NULL); 
	NODE *pDel = lp->head->next;

	void *first = pDel->data;
	lp->head->next = pDel->next;
	pDel->next->prev = lp->head;
	free(pDel);
	lp->count--;
	return first; 
}

//Removes the last element of the list
//Big-O O(1)
void *removeLast(LIST *lp)
{
	assert(lp != NULL); 
	NODE *pDel = lp->head->prev;

	void *last = pDel->data;
	pDel->prev->next = lp->head;
	lp->head->prev = pDel->prev;
	free(pDel);
	lp->count--;
	return last; 
}

//Returns the data of the first element
//Big-O O(1)
void *getFirst(LIST *lp)
{
	assert(lp != NULL); 
   	return(lp->head->next->data);
}

//Returns the data of the last element
//Big-O O(1)
void *getLast(LIST *lp)
{
	assert(lp != NULL); 
   	return(lp->head->prev->data);
}

//Searches through list for element and deletes it exists
//Big-O O(n)
void removeItem(LIST *lp, void *item)
{
	assert(lp->compare != NULL);
	NODE *check = lp->head->next;
	int i;

	for(i = 0; i < lp->count; i++)
	{
		if(lp->compare(item, check->data) == 0)
		{
			check->next->prev = check->prev;
			check->prev->next = check->next;
		    	free(check);
			lp->count--;
		}
		check = check->next; 	
	}
}

//Searches through array for element and returns its data
//Big-O O(n)
void *findItem(LIST *lp, void *item)
{
	assert(lp != NULL && item != NULL);
	NODE *p = lp->head->next;
	int i;

	for(i = 0; i < lp->count; i++)
	{
		if(lp->compare(item, p->data) == 0)
		{
			return (p->data);
		}
		p = p->next;
	}
	return NULL; 
}

//Returns a copy of the elements data in the list
//Big-O O(n)
void *getItems(LIST *lp)
{
	void **copy = malloc(sizeof(void *)*lp->count);
	NODE *p = lp->head->next;
	int i;

	for(i = 0; i < lp->count; i++)
	{
		copy[i] = p->data;
		p = p->next;
	}
	return copy; 
}
