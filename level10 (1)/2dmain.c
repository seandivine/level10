#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"


int main(int argc, char *argv[])
{
	if (argc < 1)
	{
		fprintf(stderr, "Must supply a text file name\n");
		exit(1);
	}
	
	int lineCount;
    char (*lines)[COLS] = loadFile2D(argv[1], &lineCount);
	
	printf("File loaded.\n");
	
	while(1)
	{
		char target[100];
		printf("Text to search for: ");
		fgets(target, 100, stdin);
		
		// Trim newline
		char *nl = strchr(target, '\n');
		if (nl) *nl = '\0';
		
		if (strcmp(target, "DONE") == 0) break;
		
		char *found = substringSearch2D(target, lines, lineCount);
		if (found)
			printf("Found: %s\n", found);
		else
			printf("Not found!\n");
	}

    free2D(lines);
}

