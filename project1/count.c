/* Lucas Voron
 * March 31, 2021
 * COEN 12
 * Lab 1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD 30

void read_all(char *);

int main(int argc, char *argv[])
{
	if(argc==1) //check that the user has given a file to read
	{
		printf("The file is not named.\n");
		return 1;
	}

	read_all(argv[1]); //calls to function that reads text file

	return 0;
}

void read_all(char *file_name)
{
	FILE *fp;
	int counter=0;
	char x[MAX_WORD];

	if((fp = fopen(file_name, "r"))==NULL) //check that the file exists and open file
	{
		printf("Cannot open file.\n");
		return;
	}

	while(fscanf(fp, "%s", x)==1) //counts number of words and increments counter
		counter++;

	printf("Number of words: %d\n", counter);
	
	fclose(fp); //close opened file
	return;
}
