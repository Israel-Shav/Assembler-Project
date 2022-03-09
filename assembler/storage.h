/**
 * @brief Constants:
 */

/**
 * @brief Prototypes:
 */

/**
 * @brief 
 * @return if the process is succeed
 */
bool init_storage()
{
    return True;
}

/**
 * @brief 
 * @return if the process is succeed
 */
bool encode_data(char *attribute, int data_len, ...);

/**
 * @brief 
 * @return if the process is succeed
 */
bool first_encode_instruction(char *instruction);
/**
 * @brief 
 * @return if the process is succeed
 */
bool second_encode_instruction(char *instruction);

/**
 * @brief 
 * @return if the process is succeed
 */
bool pre_second_phase_data_update();

/**
 * @brief 
 */
void storage_dispose();

/**
 * @brief Enums:
 */
