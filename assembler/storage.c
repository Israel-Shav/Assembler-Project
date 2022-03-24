#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "globals.h"
#include "storage.h"
#include "tables.h"
#include "errors.h"
#include "utils.h"

/**
 * @brief 
 * 
 * @param decimal
 * @param bit_size 
 */
static void print_bits(int decimal, unsigned int bit_size);

/**
 * @brief 
 * 
 */
static int DC, IC, DCF, ICF, IC_COUNTER;

/**
 * @brief "instructions" data from top to bottom and "data" data from bottom to top
 *         before output phase we resort "data" data
 * 
 */
static machine_word *storage[MEMORY_CAPACITY];

/**
 * @brief 
 * 
 */
static struct action_element op_fuct_table[] = {
		{"mov", MOV_OP, NONE_FUNCT, 2},
		{"cmp",CMP_OP, NONE_FUNCT, 2},
		{"add",ADD_OP, ADD_FUNCT, 2},
		{"sub",SUB_OP, SUB_FUNCT, 2},
		{"lea",LEA_OP, NONE_FUNCT, 2},
		{"clr",CLR_OP, CLR_FUNCT, 1},
		{"not",NOT_OP, NOT_FUNCT, 1},
		{"inc",INC_OP, INC_FUNCT, 1},
		{"dec",DEC_OP, DEC_FUNCT, 1},
		{"jmp",JMP_OP, JMP_FUNCT, 1},
		{"bne",BNE_OP, BNE_FUNCT, 1},
		{"jsr",JSR_OP, JSR_FUNCT, 1},
		{"red",RED_OP, NONE_FUNCT, 1},
		{"prn",PRN_OP, NONE_FUNCT, 1},
		{"rts",RTS_OP, NONE_FUNCT, 0},
		{"stop",STOP_OP, NONE_FUNCT, 0},
		{NULL, NONE_OP, NONE_FUNCT, 0}
};


/**
 * @brief 
 * 
 * @param action_name 
 * @return true 
 * @return false 
 */
bool is_action_exist(char *action_name)
{
	int i;

	if(action_name == NULL)
		return False;
	for(i = 0; i < sizeof(op_fuct_table) / sizeof(action_element); i++)
		if(op_fuct_table != NULL && op_fuct_table[i].action != NULL && strcmp(op_fuct_table[i].action, action_name) == 0)
			return True;
    return False;
}

/**
 * @brief Get the action object
 * 
 * @param action_name 
 * @return action_element* 
 */
action_element *get_action(char *action_name)
{
	int i;

	if(action_name == NULL)
		return False;
	for(i = 0; i < (sizeof(op_fuct_table) / sizeof(action_element)) - 1; i++)
		if(op_fuct_table != NULL && op_fuct_table[i].action != NULL && strcmp(op_fuct_table[i].action, action_name) == 0)
			return op_fuct_table + i;
    return op_fuct_table + i;
}

/**
 * @brief 
 * 
 * @param register_name 
 * @return true 
 * @return false 
 */
reg is_register(char *register_name)
{
	int val;
	if(register_name == NULL || strlen(register_name) == 0 || register_name[0] != 'r')
	{
		return NONE_REG;
	}
	val = (int)strtol(register_name + 1,(char **)NULL, 10);
    if(val >= 0 && val <= 15)
	    return val;
    
    return NONE_REG;
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool init_storage()
{
    DC = DEFAULT_DC;
    IC_COUNTER = IC = DEFAULT_IC;
    ICF = DCF = DEFAULT_IC_DC_FINAL;

    return True;
}

/**
 * @brief 
 * 
 * @param attribute 
 * @param data 
 * @param filename 
 * @param line_number 
 * @return true 
 * @return false 
 */
bool encode_data(char *attribute, char *data, char *filename, int line_number)
{
    if  (strcmp(attribute, ".string") == 0)
    {
        /* Check quotes */
        data_word *dataWord;
        int index;
        bool in_quotes, found;
        for (index = 0, found = in_quotes = False; data[index] != STRING_END  && data[index] != EOF && data[index] != NEW_LINE; index++)
        {
            if(!in_quotes)
                SKIP_WHITE_CHARS(data, index)
            if (data[index] == QUOTE)
            {
                if(in_quotes)
                    in_quotes = False;
                else
                    in_quotes = True;
                if(in_quotes && found)
                {
                    printf(STRING_NOT_VALID, filename, line_number, data);
                    return False;
                }
                if(!found)
                    found = True;
            }
            else if(in_quotes)
            {
                dataWord = (data_word *)malloc_with_check(sizeof(data_word));
                storage[MEMORY_CAPACITY - 1 - DC] = (machine_word *)malloc_with_check(sizeof(machine_word));
                (storage[MEMORY_CAPACITY - 1 - DC]->word).data = dataWord;
                dataWord->data = data[index];
                dataWord->ERA = 4;
                dataWord->END = 0;
                DC++;
            }
            else
            {
                printf("%c\n", data[index]);
                printf(STRING_NOT_VALID, filename, line_number, data);
                return False;
            }
            if(!in_quotes)
                SKIP_WHITE_CHARS(data, index)
        }
        dataWord = (data_word *)malloc_with_check(sizeof(data_word));
        storage[MEMORY_CAPACITY - 1 - DC] = (machine_word *)malloc_with_check(sizeof(machine_word));
        (storage[MEMORY_CAPACITY - 1 - DC]->word).data = dataWord;
        dataWord->data = STRING_END;
        dataWord->ERA = 4;
        dataWord->END = 0;
        DC++;
        return True;
    }
    else if (strcmp(attribute, ".data") == 0)
    {
        /* Check commas */
        data_word *dataWord;
        char temp[MAX_LINE_LENGTH], *temp_ptr;
        int i, index;
        long val;
        bool end_with_comma;
        for (index = 0, end_with_comma = False; data[index] != STRING_END && data[index] != EOF &&
         data[index] != NEW_LINE && data[index] != TAB; index++)
        {
            SKIP_WHITE_CHARS(data, index)
            if (data[index] == COMMA)
            {
                printf(DATA_NOT_VALID_COMMA, filename, line_number, data);
                return False;
            }
            end_with_comma = False;
            for (i = 0;
                data[index] && data[index] != EOF && data[index] != TAB &&
                data[index] != SPACE && data[index] != COMMA &&
                data[index] != NEW_LINE; index++, i++) 
            {
                temp[i] = data[index];
            }

            /* End of string */
            temp[i] = STRING_END; 

            if (!is_integer(temp)) 
            {
                printf(DATA_NOT_VALID, filename, line_number, data);
                return False;
            }
            /* Now let's write to data buffer */
            val = strtol(temp, &temp_ptr, 10);
            
            dataWord = (data_word *)malloc_with_check(sizeof(data_word));
            storage[MEMORY_CAPACITY - 1 - DC] = (machine_word *)malloc_with_check(sizeof(machine_word));
            (storage[MEMORY_CAPACITY - 1 - DC]->word).data = dataWord;
            dataWord->data = val;
            dataWord->ERA = 4;
            dataWord->END = 0;
            DC++;

            SKIP_WHITE_CHARS(data, index)

            if (data[index] == COMMA)
            {
                end_with_comma = True;
                index++;
            }
        }
        SKIP_WHITE_CHARS(data, index);
        if(end_with_comma)
        {
            printf(DATA_NOT_VALID_COMMA, filename, line_number, data);
            return False;
        }
        return True;
    }
    printf(UNKNOWN_DATA_ATTRIBUTE, filename, line_number, attribute);
    return False;
}


/**
 * @brief 
 * 
 * @param operand 
 * @param codeWord 
 * @param is_first_operand 
 * @return true 
 * @return false 
 */
static bool first_phase_opreand_update(char *operand, code_word *codeWord, bool is_first_operand);


/**
 * @brief 
 * 
 * @param operand 
 * @param codeWord 
 * @param is_first_operand 
 * @return true 
 * @return false 
 */
static bool first_phase_opreand_update(char *operand, code_word *codeWord, bool is_first_operand)
{
    char *token, *temp_str;
    label_node *node;
    data_word *dataWord;
    int addr, register_id;
    addr = register_id = 0;

    if(operand == NULL)
        return False;

    if(strlen(operand) > 0 && operand[0] == '#')
    {
        dataWord = (data_word *)malloc_with_check(sizeof(data_word));
        storage[IC] = (machine_word *)malloc_with_check(sizeof(machine_word));
        (storage[IC]->word).data = dataWord;
        dataWord->data = (int)strtol(operand + 1, (char **)NULL, 10);
        dataWord->ERA = 4;
        dataWord->END = 0;
        IC++;
    }
    else if(((node = get_label(operand)) != NULL || (is_register(operand) == NONE_REG && !is_action_exist(operand))) && is_valid_label_name(operand))
    {
        addr = 1;
        dataWord = (data_word *)malloc_with_check(sizeof(data_word));
        storage[IC] = (machine_word *)malloc_with_check(sizeof(machine_word));
        (storage[IC]->word).data = dataWord;
        dataWord->data = 0;
        dataWord->ERA = 4;
        dataWord->END = 0;
        IC++;
        dataWord = (data_word *)malloc_with_check(sizeof(data_word));
        storage[IC] = (machine_word *)malloc_with_check(sizeof(machine_word));
        (storage[IC]->word).data = dataWord;
        dataWord->data = 0;
        dataWord->ERA = 4;
        dataWord->END = 0;
        IC++;
    }
    else if((register_id = is_register(operand)) != NONE_REG)
    {
        addr = 3;
        register_id = register_id;
    }
    else
    {
        temp_str = (char *)malloc_with_check(strlen(operand) + 1);
        strcpy(temp_str, operand);
        token = strtok(temp_str, TOKENS_DELIMITERS_SECOND_ADDR);
        if(((node = get_label(token)) != NULL || (is_register(token) == NONE_REG && !is_action_exist(token))) && is_valid_label_name(token))
        {
            token = strtok(NULL, TOKENS_DELIMITERS_SECOND_ADDR);
            if(token == NULL || (register_id = is_register(token)) == NONE_REG)
            {
                free(temp_str);
                return False;
            }
            free(temp_str);
            addr = 2;
            dataWord = (data_word *)malloc_with_check(sizeof(data_word));
            storage[IC] = (machine_word *)malloc_with_check(sizeof(machine_word));
            (storage[IC]->word).data = dataWord;
            dataWord->data = 0;
            dataWord->ERA = 4;
            dataWord->END = 0;
            IC++;
            dataWord = (data_word *)malloc_with_check(sizeof(data_word));
            storage[IC] = (machine_word *)malloc_with_check(sizeof(machine_word));
            (storage[IC]->word).data = dataWord;
            dataWord->data = 0;
            dataWord->ERA = 4;
            dataWord->END = 0;
            IC++;
        }
        else
        {
            free(temp_str);
            return False;
        }
    }


    if(is_first_operand)
    {
        codeWord->src_addressing = addr;
        codeWord->src_register = register_id;
    }
    else
    {
        codeWord->dest_addressing = addr;
        codeWord->dest_register = register_id;
    }
    return True;
}

/**
 * @brief 
 * 
 * @param action 
 * @param operands 
 * @param filename 
 * @param line_number 
 * @return true 
 * @return false 
 */
bool first_encode_instruction(char *action, char *operands, char *filename, int line_number)
{
    action_element *action_e;
    opcode_word *opcodeWord;
    code_word *codeWord;
    char *token, *token_sec, *temp_str;

    if ((action_e = get_action(action)) == NULL || action_e->action == NULL)
    {
        printf(ACTION_NOT_EXIST, filename, line_number, action);
        return False;
    }

    if(action_e->opCount >= 0)
    {
        opcodeWord = (opcode_word *)malloc_with_check(sizeof(opcode_word));
        storage[IC] = (machine_word *)malloc_with_check(sizeof(machine_word));
        (storage[IC]->word).opcode = opcodeWord;
        opcodeWord->opcode = pow(2, action_e->op);
        opcodeWord->ERA = 4;
        opcodeWord->END = 0;
        IC++;
    }
    
    if(action_e->opCount > 0)
    {
        temp_str = (char *)malloc_with_check(sizeof(operands)+1);
        strcpy(temp_str, operands);
        token = strtok(temp_str, TOKENS_DELIMITERS_COMMA);
        token_sec = strtok(NULL, TOKENS_DELIMITERS_COMMA);
    }

    if(operands && token != NULL && action_e->opCount >= 1)
    {
        codeWord = (code_word *)malloc_with_check(sizeof(code_word));
        storage[IC] = (machine_word *)malloc_with_check(sizeof(machine_word));
        (storage[IC]->word).code = codeWord;
        codeWord->funct = action_e->fun;
        codeWord->src_addressing = codeWord->src_register = codeWord->dest_addressing = codeWord->dest_register = 0;
        codeWord->ERA = 4;
        codeWord->END = 0;
        IC++;
        if(!first_phase_opreand_update(token, codeWord, action_e->opCount == 2))
        {
            printf(OPERANDS_NOT_VALID, filename, line_number, operands);
            free(temp_str);
            return False;
        }
        token = strtok(NULL, TOKENS_DELIMITERS_COMMA);
        if(action_e->opCount == 1 && token != NULL)
        {
            printf(NUM_OPERANDS_NOT_VALID, filename, line_number, operands);
            free(temp_str);
            return False;
        }
        else if(action_e->opCount == 2 && token_sec != NULL)
        {
            if(!first_phase_opreand_update(token_sec, codeWord, False))
            {
                printf(OPERANDS_NOT_VALID, filename, line_number, operands);
                free(temp_str);
                return False;
            }
            token = strtok(NULL, TOKENS_DELIMITERS_COMMA);
            if(token != NULL)
            {
                printf(NUM_OPERANDS_NOT_VALID, filename, line_number, operands);
                free(temp_str);
                return False;
            }
        }
        /*else
        {
            printf(OPERANDS_NOT_VALID, filename, line_number, operands);
            free(temp_str);
            return False;
        }*/
        free(temp_str);
        return True;
    }
    else if(action_e->opCount !=  0)
    {
        printf(OPERANDS_NOT_VALID, filename, line_number, operands);
        free(temp_str);
        return False;
    }
    return True;
}

/**
 * @brief 
 * @return if the process is stable
 */
bool pre_second_phase_data_update()
{
    ICF = IC;
    DCF = DC;
    IC_COUNTER = DEFAULT_IC;
    return after_first_phase_update(ICF);
}

/**
 * @brief 
 * 
 * @param word_name 
 * @param ic_counter 
 */
static void second_phase_word_update(char *word_name);


/**
 * @brief 
 * 
 * @param word_name 
 * @param ic_counter 
 */
static void second_phase_word_update(char *word_name)
{
    label_node *node;
    char *temp_str, *token;
    int is_external_label;
    reg register_id;

    if(word_name == NULL)
        return;

    if(strlen(word_name) > 0 && word_name[0] == '#')
    {
        IC_COUNTER++;
    }
    else if((node = get_label(word_name)) != NULL)
    {
        is_external_label = node->attribute[0] != NULL && strcmp(".extern", node->attribute[0]) == 0 ? 1 : 2;
        /* Update first word in storage in place IC_COUNTER */
        if(IC_COUNTER >= DEFAULT_IC && IC_COUNTER < MEMORY_CAPACITY)
        {
            storage[IC_COUNTER]->word.data->data = node->base;
            storage[IC_COUNTER]->word.data->ERA = is_external_label;
        }
        if(is_external_label == 1)
            insert_external_label(word_name, IC_COUNTER, IC_COUNTER + 1);
        IC_COUNTER++;
        /* Update second word in storage in place IC_COUNTER */
        if(IC_COUNTER >= DEFAULT_IC && IC_COUNTER < MEMORY_CAPACITY)
        {
            storage[IC_COUNTER]->word.data->data = node->offset;
            storage[IC_COUNTER]->word.data->ERA = is_external_label;
        }
        IC_COUNTER++;
    }
    else 
    {
        temp_str = (char *)malloc_with_check(strlen(word_name) + 1);
        strcpy(temp_str, word_name);
        token = strtok(temp_str, TOKENS_DELIMITERS_SECOND_ADDR);
        if((node = get_label(token)) != NULL)
        {
            token = strtok(NULL, TOKENS_DELIMITERS_SECOND_ADDR);
            if(token == NULL || (register_id = is_register(token)) == NONE_REG)
            {
                free(temp_str);
                return;
            }
            is_external_label = node->attribute[0] != NULL && strcmp(".extern", node->attribute[0]) == 0 ? 1 : 2;
            /* Update first word in storage in place IC_COUNTER */
            if(IC_COUNTER >= DEFAULT_IC && IC_COUNTER < MEMORY_CAPACITY)
            {
                storage[IC_COUNTER]->word.data->data = node->base;
                storage[IC_COUNTER]->word.data->ERA = is_external_label;
            }
            if(is_external_label == 1)
                insert_external_label(word_name, IC_COUNTER, IC_COUNTER + 1);
            IC_COUNTER++;
            /* Update second word in storage in place IC_COUNTER */
            if(IC_COUNTER >= DEFAULT_IC && IC_COUNTER < MEMORY_CAPACITY)
            {
                storage[IC_COUNTER]->word.data->data = node->offset;
                storage[IC_COUNTER]->word.data->ERA = is_external_label;
            }
            IC_COUNTER++;
            
        }
        free(temp_str);
    }
}


/**
 * @brief 
 * 
 * @param action 
 * @param operands 
 * @param filename 
 * @param line_number 
 * @return true 
 * @return false 
 */
bool second_encode_instruction(char *action, char *operands, char *filename, int line_number)
{
    action_element *action_e;
    char *token, *token_sec, *temp_str;

    if ((action_e = get_action(action)) == NULL || action_e->action == NULL)
    {
        printf(ACTION_NOT_EXIST, filename, line_number, action);
        return False;
    }

    if(action_e->opCount > 0)
    {
        temp_str = (char *)malloc_with_check(sizeof(operands)+1);
        strcpy(temp_str, operands);
        token = strtok(temp_str, TOKENS_DELIMITERS_COMMA);
        token_sec = strtok(NULL, TOKENS_DELIMITERS_COMMA);
    }
    if(action_e->opCount == 0)
        IC_COUNTER++;
    else if(operands && token != NULL)
    {
        if(action_e->opCount == 1)
        {
            IC_COUNTER += 2;
            second_phase_word_update(token);
        }
        else if(action_e->opCount == 2)
        {
            IC_COUNTER += 2;
            second_phase_word_update(token);
            if(token_sec != NULL)
            {
                second_phase_word_update(token_sec);
            }
            else 
            {
                printf(OPERANDS_NOT_VALID, filename, line_number, operands);
                free(temp_str);
                return False;
            }
        }
        else
        {
            printf(OPERANDS_NOT_VALID, filename, line_number, operands);
            free(temp_str);
            return False;
        }

    }
    else
    {
        printf(OPERANDS_NOT_VALID, filename, line_number, operands);
        free(temp_str);
        return False;
    }
    return True;
}

/**
 * @brief Get the dc object
 * 
 * @return int 
 */
int get_dc()
{
    return DC;
}

/**
 * @brief Get the ic object
 * 
 * @return int 
 */
int get_ic()
{
    return IC;
}

/**
 * @brief Create a object file object
 * 
 * @param new_filename 
 */
void create_object_file(char *new_filename)
{
    int ic_counter, dc_counter;
    FILE *object_file;
    object_word *object;

    /* Open file, skip on failure, current assembly file descriptor to process */
	object_file = fopen(new_filename, WRITE_PERMISSIONS);
	if (object_file == NULL) 
	{
		/* if file couldn't be opened, write to stderr. */
		printf(WRITING_PERMISSIONS_ERROR, new_filename);
		return;
	}
    fprintf(object_file, "%d %d\n", ICF - DEFAULT_IC, DCF);
    for (ic_counter = DEFAULT_IC; ic_counter < ICF; ic_counter++)
    {
        object = storage[ic_counter]->word.object;
        fprintf(object_file, "%.4d A%x-B%x-C%x-D%x-E%x%s", ic_counter , object->A, object->B, object->C, object->D, object->E, NEW_LINE_STR);
    }

    for(dc_counter = MEMORY_CAPACITY - 1 ; dc_counter >= MEMORY_CAPACITY - DCF; dc_counter--)
	{
        object = storage[dc_counter]->word.object;
        fprintf(object_file, "%.4d A%x-B%x-C%x-D%x-E%x%s", ic_counter + (MEMORY_CAPACITY - 1 - dc_counter)  , object->A, object->B, object->C, object->D, object->E, NEW_LINE_STR);
	}
	fclose(object_file);
}


/**
 * @brief 
 * 
 */
void storage_dispose()
{
    int i;
	for(i = DEFAULT_IC; i < IC; i++)
	{
        free((storage[i]->word).opcode);
        free(storage[i]);
	}
    IC = DEFAULT_IC;
    for(i = (MEMORY_CAPACITY - DC); i < MEMORY_CAPACITY; i++)
	{
        free((storage[i]->word).data);
        free(storage[i]);
	}
    DC = DEFAULT_DC;
    ICF = DCF = DEFAULT_IC_DC_FINAL;
}

/**
 * @brief 
 * 
 */
void print_storage_table()
{
    int i;
	printf("Instructions\n");
	for(i = DEFAULT_IC; i < IC; i++)
	{
        print_bits(storage[i]->word.opcode->END, 1);
		printf(" | ");
        print_bits(storage[i]->word.opcode->ERA, 3);
        printf(" | ");
        print_bits(storage[i]->word.opcode->opcode, MAX_DATA_WORD_SIZE);
        printf(" \n");
	}
    printf("Data\n");
    for(i = (MEMORY_CAPACITY - DC); i < MEMORY_CAPACITY; i++)
	{
        print_bits(storage[i]->word.data->END, 1);
		printf(" | ");
        print_bits(storage[i]->word.data->ERA, 3);
        printf(" | ");
        print_bits(storage[i]->word.data->data, MAX_DATA_WORD_SIZE);
        printf(" \n");
	}
}

/**
 * @brief 
 * 
 * @param decimal 
 * @param bit_size 
 */
static void print_bits(int decimal, unsigned int bit_size)
{
    int length, counter, *binary;
    binary = (int *)calloc(bit_size, sizeof(int));
    counter = 0;
    if (decimal < 0) 
        decimal += pow(2, bit_size);
    while(decimal > 0) {
            binary[counter] = decimal % 2;
            decimal = decimal / 2;
            counter++;
    }
    for (length = bit_size - 1; length >=0; length--) {
            printf("%d", binary[length]);
    }
}