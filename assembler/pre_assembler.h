/**
 * @brief Constants:
 */

#define SOURCE_FILE_EXTENSION ".as"

#define AFTER_MACRO_DIR "./after_macro"

#define MACRO_START_STATEMENT "macro"

#define MACRO_END_STATEMENT "endm"

/**
 * @brief Prototypes:
 */

/**
 * @brief Creates copy of source file, replace any macro statement with its content and removes unnecessary macros definitions
 * @param filename Extensionless file name
 * @return After macro phase edit source file
 */
char *macro_phase_process(char *filename);

/**
 * @brief Processes a single line in the macro phase
 * @param line The line text
 * @param is_macro_block Is reading macro block
 * @param macro_name Macro name
 * @return Whether succeeded.
 */
static bool macro_line_process(char *line, bool *is_macro_block, char *macro_name, FILE* new_file);

/**
 * @brief Enums:
 */