#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Must supply a text file name\n");
        return 1;
    }

    int lineCount;
    char **lines = loadFileAA(argv[1], &lineCount);

    printf("File loaded.\n");

    while (1)
    {
        char target[100];
        printf("Text to search for: ");

        if (fgets(target, sizeof(target), stdin) == NULL)
        {
            break;
        }

        char *nl = strchr(target, '\n');
        if (nl)
        {
            *nl = '\0';
        }

        if (strcmp(target, "DONE") == 0)
        {
            break;
        }

        char *found = substringSearchAA(target, lines, lineCount);
        if (found)
        {
            printf("Found: %s\n", found);
        }
        else
        {
            printf("Not found!\n");
        }
    }

    freeAA(lines, lineCount);
    return 0;
}