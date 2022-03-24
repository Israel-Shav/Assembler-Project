/**
 * @brief Constants:
 */

/* Maximum length of a single source line, exclude \n and \0  */
#define MAX_LINE_LENGTH 80

#define TOKENS_DELIMITERS "\n\t\r "

#define TOKENS_DELIMITERS_COLON "\n\t\r :"

#define TOKENS_DELIMITERS_WO_SPACE "\n\t\r"

#define COMMENT ';'

#define COMMA ','

#define QUOTE '"'

#define TAB '\t'

#define STRING_END '\0'

#define SPACE ' '

#define NEW_LINE '\n'

#define NEW_LINE_STR "\n"

#define NEW_LINE_DELIMITERS "\r" NEW_LINE_STR

#define READ_PERMISSIONS "r"

#define WRITE_PERMISSIONS "w"

#define TOKENS_DELIMITERS_COMMA "\n\t\r ,"

#define TOKENS_DELIMITERS_SECOND_ADDR "[]"

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


/**
 * @brief Structs:
 */

/* Registers */
typedef enum registers {
	R0 = 0,
	R1,
	R2,
	R3,
	R4,
	R5,
	R6,
	R7,
    R8,
    R9,
    R10,
    R11,
    R12,
    R13,
    R14,
    R15,
	NONE_REG = -1
} reg;