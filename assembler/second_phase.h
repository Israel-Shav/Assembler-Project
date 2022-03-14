/**
 * @brief Constants:
 */

/**
 * @brief Prototypes:
 */

/**
 * @brief Allocates and builds the data inside the machine words storge by the given operand
 * @param full_filename The current code image
 * @return Whether succeeded.
 */
bool second_phase_process(char *full_filename);

/**
 * @brief Processes a single line in the second phase
 * @param line The line text
 * @param bool Indicates if process stable
 * @return Whether succeeded.
 */
static bool sp_line_process(char *line, bool *is_process_stable, char *filename, int line_number);

/**
 * @brief Enums:
 */

