#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "fileutil.h"

static size_t trimNewline(char *line, size_t length)
{
    while (length > 0 &&
           (line[length - 1] == '\n' || line[length - 1] == '\r'))
    {
        length--;
    }

    line[length] = '\0';
    return length;
}

char ** loadFileAA(char *filename, int *size)
{
    FILE *in = fopen(filename, "r");
    if (!in)
    {
        perror("Can't open file");
        exit(1);
    }

    char **arr = NULL;
    int count = 0;
    int capacity = 0;

    char *buffer = NULL;
    size_t bufferCapacity = 0;
    ssize_t charsRead;

    while ((charsRead = getline(&buffer, &bufferCapacity, in)) != -1)
    {
        size_t length = trimNewline(buffer, (size_t)charsRead);

        if (count == capacity)
        {
            int newCapacity = (capacity == 0) ? 8 : capacity * 2;
            char **bigger = realloc(arr, (size_t)newCapacity * sizeof(*arr));

            if (!bigger)
            {
                fprintf(stderr, "Not enough memory to load the file.\n");
                free(buffer);
                fclose(in);
                freeAA(arr, count);
                exit(1);
            }

            arr = bigger;
            capacity = newCapacity;
        }

        arr[count] = malloc(length + 1);
        if (!arr[count])
        {
            fprintf(stderr, "Not enough memory to load the file.\n");
            free(buffer);
            fclose(in);
            freeAA(arr, count);
            exit(1);
        }

        strcpy(arr[count], buffer);
        count++;
    }

    free(buffer);
    fclose(in);
    *size = count;
    return arr;
}

char (*loadFile2D(char *filename, int *size))[COLS]
{
    FILE *in = fopen(filename, "r");
    if (!in)
    {
        perror("Can't open file");
        exit(1);
    }

    char (*arr)[COLS] = NULL;
    int count = 0;
    int capacity = 0;

    char *buffer = NULL;
    size_t bufferCapacity = 0;
    ssize_t charsRead;

    while ((charsRead = getline(&buffer, &bufferCapacity, in)) != -1)
    {
        size_t length = trimNewline(buffer, (size_t)charsRead);

        /* Leave room for the '\0' at the end of each row. */
        if (length >= COLS)
        {
            length = COLS - 1;
            buffer[length] = '\0';
        }

        if (count == capacity)
        {
            int newCapacity = (capacity == 0) ? 8 : capacity * 2;
            char (*bigger)[COLS] =
                realloc(arr, (size_t)newCapacity * sizeof(*arr));

            if (!bigger)
            {
                fprintf(stderr, "Not enough memory to load the file.\n");
                free(buffer);
                fclose(in);
                free(arr);
                exit(1);
            }

            arr = bigger;
            capacity = newCapacity;
        }

        strcpy(arr[count], buffer);
        count++;
    }

    free(buffer);
    fclose(in);
    *size = count;
    return arr;
}

char * substringSearchAA(char *target, char **lines, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (strstr(lines[i], target) != NULL)
        {
            return lines[i];
        }
    }

    return NULL;
}

char * substringSearch2D(char *target, char (*lines)[COLS], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (strstr(lines[i], target) != NULL)
        {
            return lines[i];
        }
    }

    return NULL;
}

void freeAA(char **arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(arr[i]);
    }

    free(arr);
}

void free2D(char (*arr)[COLS])
{
    free(arr);
}