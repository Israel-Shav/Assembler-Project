/**
 * @brief Constants:
 * 
 *  %s %d %s = FILE LINE DATA
 * %s %d %d = FILE LINE LEN
 */

#define ERR_OUTPUT_FILE stderr

#define NO_ERRORS_EC 0

#define MEMORY_ALLOC_ERROR_IN "Error: Fatal - Memory allocation failed in \"%s\".\n"
#define MEMORY_ALLOC_ERROR "Error: Fatal - Memory allocation failed.\n"
#define MEMORY_ALLOC_ERROR_EC 1

#define READING_PERMISSIONS_ERROR "Error: file \"%s.as\" is inaccessible for reading. skipping it.\n"

#define TOO_LONG_INPUT_LINE "Error in %s:%d: Line too long to process. Maximum line length should be %d.\n"

#define EMPTY_LABEL_LINE "Error in %s:%d: Empty label declaration.\n\tIn line: \"%s\"\n"

#define EMPTY_DATA_LINE "Error in %s:%d: Empty data (.string, .data) declaration.\n\tIn line: \"%s\"\n"

#define EMPTY_EXTERN_LINE "Error in %s:%d: Empty .extern declaration.\n\tIn line: \"%s\"\n"

#define UNKNOWN_INSTRUCTION "Error in %s:%d: UNKNOWN istructions.\n* instruction: \"%s\"\n"

#define LABEL_NOT_FOUND_ADD_ENTRY "Error: \"%s\" not found in labels table.\n"

#define LABEL_ALREADY_EXIST "Error in %s:%d: label \"%s\" is aready exist.\n"

#define UNKNOWN_DATA_ATTRIBUTE "Error in %s:%d: \"%s\" is NOT .data and neither .string.\n"

#define DATA_NOT_VALID "Error in %s:%d: \"%s\" is NOT valid data for .data instruction.\n"

#define DATA_NOT_VALID_COMMA "Error in %s:%d: \"%s\" is NOT valid data there is empty value between two commas.\n"

#define STRING_NOT_VALID "Error in %s:%d: %s is NOT valid string for .string instruction.\n"

#define ACTION_NOT_EXIST "Error in %s:%d: %s is NOT a valid instruction.\n"




/**
 * @brief Prototypes:
 */

/**
 * @brief Enums:
 */
