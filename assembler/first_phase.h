/**
 * @brief Constants:
 */

/**
 * @brief Prototypes:
 */

/**
 * @brief Processes a single code line in the first pass.
 *        Adds the code build binary structure to the code_img,
 *        encodes immediately-addresses operands and leaves required data word that use labels NULL.
 * @param line The code line to process
 * @param i Where to start processing the line from
 * @param ic A pointer to the current instruction counter
 * @param code_img The code image array
 * @return Whether succeeded or notssss
 */
static bool process_code(line_info line, int i, long *ic, machine_word **code_img);

/**
 * @brief Allocates and builds the data inside the additional code word by the given operand,
 *        Only in the first pass
 * @param code_img The current code image
 * @param ic The current instruction counter
 * @param operand The operand to check
 */
static void build_extra_codeword_fpass(machine_word **code_img, long *ic, char *operand);

/**
 * @brief Enums:
 */

