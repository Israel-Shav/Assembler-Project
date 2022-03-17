/**
 * @brief Constants:
 * 
 *  %s %d %s = FILE LINE DATA
 * %s %d %d = FILE LINE LEN
 */

#define ERR_OUTPUT_FILE stderr

#define NO_ERRORS_EC 0

#define MEMORY_ALLOC_ERROR_IN "Error: Fatal - Memory allocation failed in %s.\n"
#define MEMORY_ALLOC_ERROR "Error: Fatal - Memory allocation failed.\n"
#define MEMORY_ALLOC_ERROR_EC 1

#define READING_PERMISSIONS_ERROR "Error: file \"%s.as\" is inaccessible for reading. skipping it.\n"

#define TOO_LONG_INPUT_LINE "Error in %s:%d: Line too long to process. Maximum line length should be %d.\n"

#define EMPTY_LABEL_LINE "Error in %s:%d: Empty label declaration.\n\tIn line: \"%s\"\n"

#define EMPTY_DATA_LINE "Error in %s:%d: Empty data (.string, .data) declaration.\n\tIn line: \"%s\"\n"

#define EMPTY_EXTERN_LINE "Error in %s:%d: Empty .extern declaration.\n\tIn line: \"%s\"\n"

#define UNKOWN_INSTRUCTION "Error in %s:%d: Unkown istructions.\n* instruction: \"%s\"\n"

#define LABEL_NOT_FOUND_ADD_ENTRY "Error: %s not found in labels table.\n"

/**
 * @brief Prototypes:
 */

/**
 * @brief Enums:
 */
