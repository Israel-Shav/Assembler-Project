/**
 * @brief Constants:
 */

#define SOURCE_FILE_EXTENSION ".as"

#define AFTER_MACRO_DIR "./after_macro"

#define MACRO_START_STATEMENT "macro"

#define MACRO_END_STATEMENT "endm"

#define COMMENT ";"

#define NEW_LINE "\n"

#define READ_PERMISSIONS "r"

#define WRITE_PERMISSIONS "w"

/**
 * @brief Prototypes:
 */

/**
 * @brief 
 * @param filename Extensionless file name
 */
char *macro_phase_process(char *filename);

/**
 * @brief Processes a single line in the macro phase
 * @param line The line text
 * @param is_macro_block Is reading macro block
 * @param macro_name Macro name
 * @return Whether succeeded.
 */
static bool line_process(char *line, bool *is_macro_block, char *macro_name, FILE* new_file);

/**
 * @brief Enums:
 */