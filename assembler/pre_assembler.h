/**
 * @brief Constants:
 */

#define SOURCE_FILE_EXTENSION ".as"

#define DEST_FILE_EXTENSION ".am"

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
 * @brief Enums:
 */