#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "errors.h"

/**
 * Allocates memory in the required size. Exits the program if failed.
 * @param size The size to allocate in bytes
 * @return A generic pointer to the allocated memory if succeeded
 */
void *malloc_with_check(long size) 
{
	void *ptr = malloc(size);
	if (ptr == NULL) 
    {
		printf(MEMORY_ALLOC_ERROR);
		exit(MEMORY_ALLOC_ERROR_EC);
	}
	return ptr;
}

/**
 * Concatenates both string to a new allocated memory
 * @param s0 The first string
 * @param s1 The second string
 * @return A pointer to the new, allocated string
 */
char *strallocat(char *s0, char* s1) 
{
	char *str = (char *)malloc_with_check(strlen(s0) + strlen(s1) + 1);
	strcpy(str, s0);
	strcat(str, s1);
	return str;
}


/**
 * Creates
 * @param 
 * @return 
 */
char *getFileName(char *path) {
    char *retVal = path, *ptr;
    for (ptr = path; *ptr; ptr++) {
        if (*ptr == '/' || *ptr == '\\' || *ptr == ':') {
            retVal = ptr;
        }
    }
    return retVal;
}