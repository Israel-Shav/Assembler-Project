#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "globals.h"
#include "storage.h"
#include "errors.h"
#include "utils.h"

static int DC, IC, DCF, ICF;

/**
 * @brief "instructions" data from top to bottom and "data" data from bottom to top
 *         before output phase we resort "data" data
 * 
 */

static machine_word *storage[MEMORY_CAPACITY];

static struct action_element op_fuct_table[] = {
		{"mov", MOV_OP, NONE_FUNCT},
		{"cmp",CMP_OP, NONE_FUNCT},
		{"add",ADD_OP, ADD_FUNCT},
		{"sub",SUB_OP, SUB_FUNCT},
		{"lea",LEA_OP, NONE_FUNCT},
		{"clr",CLR_OP, CLR_FUNCT},
		{"not",NOT_OP, NOT_FUNCT},
		{"inc",INC_OP, INC_FUNCT},
		{"dec",DEC_OP, DEC_FUNCT},
		{"jmp",JMP_OP, JMP_FUNCT},
		{"bne",BNE_OP, BNE_FUNCT},
		{"jsr",JSR_OP, JSR_FUNCT},
		{"red",RED_OP, NONE_FUNCT},
		{"prn",PRN_OP, NONE_FUNCT},
		{"rts",RTS_OP, NONE_FUNCT},
		{"stop",STOP_OP, NONE_FUNCT},
		{NULL, NONE_OP, NONE_FUNCT}
};

/**
 * @brief 
 * @return if the process is stable
 */
bool init_storage()
{
    DC = DEFAULT_DC;
    IC = DEFAULT_IC;
    ICF = DCF = DEFAULT_IC_DC_FINAL;

    return True;
}

/**
 * @brief 
 * @return if the process is stable
 */
bool encode_data(char *attribute, char *data, char *filename, int line_number)
{
    if  (strcmp(attribute, ".string") == 0)
    {
        /* Check quotes */
        data_word *dataWord;
        int index;
        bool in_quotes, found;
        for (index = 0, found = in_quotes = False; data[index] != STRING_END  && data[index] != EOF &&
         data[index] != NEW_LINE && data[index] != TAB; index++)
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

static void print_bits(int decima, unsigned int bit_size);

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