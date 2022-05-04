/* Lucas Voron
 * May 30, 2021
 * COEN 12L
 * Project 5 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "pqueue.h"
#include "pack.h"

static int compare(struct node *n1, struct node *n2);

int main (int argc, char *argv[])
{
	FILE *fp;
	char character;
     int i, j, counts[257], size[257];
     struct node *leaves[257], *n1, *n2, *new, *temp;
	PQ *priorityQueue;

	//Prints file requirements and checks that two files are provided for the arguments recieved
	if(argc != 3)
	{
		fprintf(stderr, "usage: %s file1 file2\n", argv[0]);
		return 1;
	}

	if ((fp = fopen(argv[1], "r")) == NULL) 
	{
		fprintf(stderr, "%s: cannot open %s\n", argv[0], argv[1]);
		return 1;
	}

	//Sets the count of characters to 0 to start
	for (i=0; i<257; i++) 
	{
		counts[i] = 0;
	}

	//Counts the number of characters
	while(fscanf(fp, "%c", &character) == 1) 
	{
		counts[(int) character]++;
	}

	
	priorityQueue = createQueue(compare);

	//Creates a binary tree that consists of one leaf for characters with non-zero counts and end of file marker
	for (i=0;i<256;i++) 
	{
		if(counts[i] > 0) 
		{
			leaves[i] = malloc(sizeof(struct node));
			assert(leaves[i] != NULL);
			leaves[i] -> count = counts[i];
			leaves[i] -> parent = NULL;
			addEntry(priorityQueue, leaves[i]);
		}
		else
			leaves[i] = NULL;
	}

	leaves[256] = malloc(sizeof(struct node));
	assert(leaves[256] != NULL);
	leaves[256] -> count = 0;
	leaves[256] -> parent = NULL;
	addEntry(priorityQueue, leaves[256]);

	//If the priority queue has more than a single tree, the program creates a new tree with low priority trees becoming a part of the new tree
	while (numEntries(priorityQueue) > 1) 
	{
		new = malloc(sizeof(struct node));
		assert(new != NULL);
		n1 = removeEntry(priorityQueue);
		n2 = removeEntry(priorityQueue);
		n1 -> parent = new;
		n2 -> parent = new;
	  	new -> count = (n1->count + n2->count);
	 	new -> parent = NULL;
	    	addEntry(priorityQueue, new);
	}

	fclose(fp);

	//Checks if the second file can be opened
	if ((fp = fopen(argv[2], "w")) == NULL) 
	{
		fprintf(stderr, "%s: Cannot open %s\n", argv[0], argv[1]);
		return 1;
	}

	fclose(fp);

	//Finds the number of non-zero characters in the input file
	for(i=0;i<257;i++) 
	{
		if(leaves[i] != NULL) 
		{
			j = 0;
			temp = leaves[i];
			while(temp -> parent != NULL) 
			{
				j++;
				temp = temp -> parent;
			}
			size[i] = j;
	 	}
	}
	
	//Prints the count of characters and number of bits needed to store each character
	for(i=0;i<257;i++) 
	{
	    	if (leaves[i] != NULL)
		{
			if(isprint(i)) 
			{
				fprintf(stdout, "\'%c\'", i);
			}
			else 
			{
				fprintf(stdout, "%03o", i);
			}
			fprintf(stdout, ": %d x %d bits = %d bits\n", counts[i], size[i], counts[i] * size[i]);
		}
	}

	//Uses the pack function given to compress file
	pack(argv[1], argv[2], leaves);
	
	return 0;
}

static int compare(struct node *n1, struct node *n2) 
{
	return (n1->count < n2->count) ? -1 : (n1->count > n2->count);
}
