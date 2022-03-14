#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "tables.h"
#include "utils.h"

/**
 * @brief 
 */
void tables_dispose()
{
    
}

/**
 *  
 * 
 *  @brief Instructions table section:
 * 
 */


/**
 * @brief 
 * @return if instruction_word is .string ot .data
 */
bool is_data_instruction(char *instruction_word)
{
	if (strcmp(instruction_word, ".string") == 0 || strcmp(instruction_word, ".data") == 0)
		return True;
	return False;
}

/**
 * @brief 
 * @return if instruction_word is .extern or .entry
 */
bool is_linked_instruction(char *instruction_word)
{
	if (strcmp(instruction_word, ".extern") == 0 || strcmp(instruction_word, ".entry") == 0)
		return True;
	return False;
}

/**
 *  
 * 
 *  @brief Actions table section:
 * 
 */

struct action_element op_fuct_table[] = {
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
 * @return if action exist
 */
bool is_action_exist(char *action_name)
{
    return True;
}

/**
 *  
 * 
 *  @brief Macros table section:
 * 
 */

static macro **macros_table;

/**
 * @brief 
 * @return if the process is succeed
 */
bool init_macro_table()
{
    return True;
}

/**
 * @brief 
 * @return if the process is succeed
 */
bool insert_macro(char *macro_name, char *new_line)
{
    return True;
}

/**
 * @brief 
 * @return Requested marco's code
 */
char *get_macro_code(char *macro_name)
{
	/* If not exist return NULL */
    return NULL;
}

/**
 *  
 * 
 *  @brief Labels table section:
 * 
 */

static label **labels_table;

/**
 * @brief 
 * @return if the process is succeed
 */
bool init_labels_table()
{
    return True;
}

/**
 * @brief 
 * @return if the process is succeed
 */
bool insert_label(char *label_name, char *attribute, int base, int offset)
{
    return True;
}

/**
 * @brief 
 * @return if the process is succeed
 */
bool add_entry_attribute(char *label_name)
{
    return True;
}

/**
 * @brief 
 * @return if label_name is label
 */
bool is_label(char *label_name)
{
	int i = 0;

	/* Skip white chars at the beginning anyway */
	SKIP_WHITE_CHARS(label_name, i)

	/* Let's allocate some memory to the string needed to be returned */
	for (; label_name[i] && 
			label_name[i] != ':' && 
			label_name[i] != ' ' && 
			label_name[i] != '\t' && 
			label_name[i] != '\n' && 
			label_name[i] != EOF && 
			i <= MAX_LINE_LENGTH;
			 i++)
		;

	/* if it was a try to define label, print errors if needed. */
	if (label_name[i] == ':')
	{ 
		i++;
		if(label_name[i] && label_name[i] != ' ' && label_name[i] != '\t' && 
			label_name[i] != '\n' && label_name[i] != EOF )
			return False;

		return True;
	}

	return False; /* There was no error */
}
