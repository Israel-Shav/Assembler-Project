/**
 * @brief Constants:
 */

/* moves the index to the next place in string where the char isn't white */
#define SKIP_WHITE_CHARS(string, index) \
        for (;string[(index)] && (string[(index)] == '\t' || string[(index)] == ' '); (++(index)))\
        ;

/* moves the index to the next place in string where the char isn't white */
#define SKIP_WHITE_CHARS_PNT(str_pnt) \
        for (;str_pnt[0] && (str_pnt[0] == '\t' || str_pnt[0] == ' '); (++(str_pnt)))\
        ;

/**
 * @brief Prototypes:
 */

/**
 * Allocates memory in the required size. Exits the program if failed.
 * @param size The size to allocate in bytes
 * @return A generic pointer to the allocated memory if succeeded
 */
void *malloc_with_check(long size);

/**
 * Concatenates both string to a new allocated memory
 * @param s0 The first string
 * @param s1 The second string
 * @return A pointer to the new, allocated string
 */
char *strallocat(char *s0, char* s1);

/**
 * Creates
 * @param 
 * @return 
 */
char *getFileName(char *path);

/**
 * Creates
 * @param 
 * @return 
 */
bool is_integer(char *str);

/**
 * @brief Enums:
 */

