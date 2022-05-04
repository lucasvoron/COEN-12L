/* Lucas Voron
 * May 21, 2021
 * COEN 12L
 * Term Project */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"

typedef struct node
{
	void **data;
	int first;
	int count;
	int length;
	struct node *next;
	struct node *prev;
}NODE;

typedef struct list
{
	int count;
	struct node *head;
	struct node *tail;
}LIST;

NODE *newNode(int length);

//Creates a list and returns a pointer to that list
//Big-O: O(1)
LIST *createList(void)
{
	LIST *lp = malloc(sizeof(LIST));
	lp->head = lp->tail = newNode(sizeof(NODE));
	lp->count = 0;
}

//Function that is called to create a new node and returns a pointer to that node
//Big-O: O(1)
NODE *newNode(int length)
{
	NODE *np = malloc(sizeof(NODE));
	assert(np != NULL);

	length = 20;
	np->data = malloc(sizeof(void **) *length);
	np->count = 0;
	np->first = 0;
	
	np->length = length;
	np->next = NULL;
	np->prev = NULL;
	return np;
}

//Functions goes through the lsit and frees each node and the data within it
//Big-O O(n)
void destroyList(LIST *lp)
{
	assert(lp != NULL);
 	NODE *np;

 	while (lp->head != NULL) 
	{
		np = lp->head;
		lp->head = lp->head->next;
		free(np->data);
		free(np);
 	}
	free(lp);
}

//Returns the number of items within the list by returning the count
//Big-O O(1)
int numItems(LIST *lp)
{
	assert(lp != NULL);

    	return lp->count;
}

//Checks to see if the first node is full and then creates a new node of a constant length
//Big-O O(1)
void addFirst(LIST *lp, void *item)
{
	assert(lp != NULL && item != NULL);
	
	if(lp->head->count == lp->head->length)
	{
		NODE *np = newNode(lp->head->length);
		np->next = lp->head;
		lp->head = np;
		np->next->prev = np;
	}

	int index = ((lp->head->first + lp->head->length - 1) % lp->head->length);
	lp->head->data[index] = item;
	lp->head->first = index;
	lp->head->count++;
	lp->count++;
}

//Checks to see if the last node is full and then creates a new node of constant length
//Big-O O(1)
void addLast(LIST *lp, void *item)
{
	assert(lp != NULL && item != NULL);
	
	if(lp->tail->count == lp->tail->length)
	{
		NODE *np = newNode(lp->tail->length);
		np->prev = lp->tail;
		lp->tail->next = np;
		lp->tail = np;
	}

	int index = ((lp->tail->first + lp->tail->count) % lp->tail->length);
	lp->tail->data[index] = item;
	lp->tail->count++;
	lp->count++;
}

//Removes the first element in the function and frees node and its data
//Big-O O(1)
void *removeFirst(LIST *lp)
{
	assert(lp != NULL); 

	if(lp->head->count == 0)
	{
		lp->head = lp->head->next;
		free(lp->head->prev);
		lp->head->prev = NULL;
	}

	int index = lp->head->first;
	int newindex = (index+1) % lp->head->length;
	lp->head->first = newindex;

	void *copy = lp->head->data[index];
	lp->head->count--;
	lp->count--;

	return copy;
}

//Removes the last element in the function and frees node and its data
//Big-O O(1)
void *removeLast(LIST *lp)
{
	assert(lp != NULL); 
	
	if(lp->tail->count == 0)
	{
		NODE *np = lp->tail;
		lp->tail = lp->tail->prev;
		lp->tail->next = NULL;
		free(np->data);
		free(np);
	}

	int index = ((lp->tail->first + lp->tail->count) % lp->tail->length);

	void *copy = lp->tail->data[index];
	lp->tail->count--;
	lp->count--;

	return copy; 
}

//Traverses the list and copies the array of the node and returns the copy
//Big-O O(logn)
void *getItem(LIST *lp, int index)
{
	assert(lp != NULL);
	assert(index >= 0 && index < lp->count);

	NODE *np = lp->head;
	
	while(index >= np->count)
	{
		index = index - np->count;
		np = np->next;
	}
	void *copy = np->data[(np->first +index) % np->length];

	return copy;
}

//Traverses the node and sorts the items
//Big-O O(1)
void setItem(LIST *lp, int index, void *item)
{
	assert(lp != NULL && item != NULL);
	assert(index >= 0 && index < lp->count);

	NODE *np = lp->head;

	while(index >= np->count)
	{
		index = index - np->count;
		np = np->next;
	}

	np->data[(np->first + index) % np->length] = item;
}
