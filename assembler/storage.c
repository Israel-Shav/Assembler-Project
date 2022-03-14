#include "globals.h"
#include "storage.h"

static int DC, IC, DCF, ICF;

static machine_word *data_storage;

static machine_word *code_storage;

/**
 * @brief 
 * @return if the process is stable
 */
bool init_storage()
{
    DC = 0;
    IC = 100;
    DCF = -1;
    ICF = -1;
    return True;
}

/**
 * @brief 
 * @return if the process is stable
 */
bool encode_data(char *attribute, char *data)
{
    return True;
}

/**
 * @brief 
 * @return if the process is stable
 */
bool first_encode_instruction(char *action, char *operands)
{
    return True;
}

/**
 * @brief 
 * @return if the process is stable
 */
bool second_encode_instruction(char *action, char *operands)
{
    return True;
}

/**
 * @brief 
 * @return if the process is stable
 */
bool pre_second_phase_data_update()
{
    return True;
}

/**
 * @brief 
 * @return DC value
 */
int get_dc()
{
    return DC;
}

/**
 * @brief 
 */
void storage_dispose()
{
    
}