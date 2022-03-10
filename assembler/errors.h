/**
 * @brief Constants:
 */

#define ERR_OUTPUT_FILE stderr

#define NO_ERRORS_EC 0

#define MEMORY_ALLOC_ERROR "Error: Fatal - Memory allocation failed.\n"
#define MEMORY_ALLOC_ERROR_EC 1

#define READING_PERMISSIONS_ERROR(S) "Error: file \"" #S ".as\" is inaccessible for reading. skipping it.\n"

#define TOO_LONG_INPUT_LINE(FILE, LINE, LEN) "Error in " #FILE ":" #LINE ": Line too long to process. Maximum line length should be " #LEN "."

/**
 * @brief Prototypes:
 */

/**
 * @brief Enums:
 */
