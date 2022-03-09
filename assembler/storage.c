#include "globals.h"
#include "storage.h"

static int DC = 0;

static int IC = 100;

static int DCF, ICF;

static machine_word **data_storage;

static machine_word **code_storage;

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
bool encode_data(char *attribute, int data_len, ...)
{
    return True;
}

/**
 * @brief 
 * @return if the process is succeed
 */
bool first_encode_instruction(char *instruction)
{
    return True;
}

/**
 * @brief 
 * @return if the process is succeed
 */
bool second_encode_instruction(char *instruction)
{
    return True;
}

/**
 * @brief 
 * @return if the process is succeed
 */
bool pre_second_phase_data_update()
{
    return True;
}

/**
 * @brief 
 */
void storage_dispose()
{
    
}