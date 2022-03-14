/**
 * @brief Constants:
 */

/* Maximum length of a single source line, exclude \n and \0  */
#define MAX_LINE_LENGTH 80

#define TOKENS_DELIMITERS "\n\t\r "

#define COMMENT ';'

#define NEW_LINE '\n'

#define NEW_LINE_STR "\n"

#define READ_PERMISSIONS "r"

#define WRITE_PERMISSIONS "w"

/**
 * @brief Prototypes:
 */

/**
 * @brief Enums:
 */

/* bool definition */
typedef enum booleans {
	False = 0,
    True = 1
} bool;