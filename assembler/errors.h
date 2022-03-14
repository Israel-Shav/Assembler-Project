/**
 * @brief Constants:
 */

#define ERR_OUTPUT_FILE stderr

#define NO_ERRORS_EC 0

#define MEMORY_ALLOC_ERROR_IN(SEC) "Error: Fatal - Memory allocation failed in " #SEC ".\n"
#define MEMORY_ALLOC_ERROR "Error: Fatal - Memory allocation failed.\n"
#define MEMORY_ALLOC_ERROR_EC 1

#define READING_PERMISSIONS_ERROR(S) "Error: file \"" #S ".as\" is inaccessible for reading. skipping it.\n"

#define TOO_LONG_INPUT_LINE(FILE, LINE, DATA) "Error in " #FILE ":" #LINE ": Line too long to process. Maximum line length should be " #DATA "."

#define EMPTY_LABEL_LINE(FILE, LINE, DATA) "Error in " #FILE ":" #LINE ": Empty label declaration.\n\tIn line: \"" #DATA "\""

#define EMPTY_DATA_LINE(FILE, LINE, DATA) "Error in " #FILE ":" #LINE ": Empty data (.string, .data) declaration.\n\tIn line: \"" #DATA "\""

#define EMPTY_EXTERN_LINE(FILE, LINE, DATA) "Error in " #FILE ":" #LINE ": Empty .extern declaration.\n\tIn line: \"" #DATA "\""

#define UNKOWN_INSTRUCTION(FILE, LINE, DATA) "Error in " #FILE ":" #LINE ": Unkown istructions.\n\tIn line: \"" #DATA "\""

#define LABEL_NOT_FOUND_ADD_ENTRY(LABEL) "Error: " #LABEL " not found in labels table."

/**
 * @brief Prototypes:
 */

/**
 * @brief Enums:
 */
