#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "tables.h"
#include "errors.h"
#include "utils.h"

/**
 * @brief 
 */

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

static labels_list *labelsList;

/**
 * @brief 
 * @return if the process is succeed
 */
static bool init_labels_table()
{
	labelsList = (labels_list *)malloc(sizeof(labels_list));
	if(labelsList == NULL)
	{
		printf(MEMORY_ALLOC_ERROR_IN("table.c -> init_labels_table() -> labelsList"));
		exit(MEMORY_ALLOC_ERROR_EC);
	}
	labelsList -> nLabels = 0;
	labelsList -> labels_table =  (label *)malloc(labelsList -> block_size = labelsList -> size = sizeof(label));
	if(labelsList -> labels_table == NULL)
	{
		free(labelsList);
		printf(MEMORY_ALLOC_ERROR_IN("table.c -> init_labels_table() -> labels_table"));
		exit(MEMORY_ALLOC_ERROR_EC);
	}
    return True;
}

/**
 * @brief 
 * @return if the process is succeed
 */
bool insert_label(char *label_name, char *attribute, int base, int offset)
{
	if(labelsList == NULL && !init_labels_table())
		return False;

	unsigned int nLabels = labelsList->nLabels;
    if (nLabels >= labelsList->size) {
        unsigned int newSize = labelsList->size + labelsList->block_size;
        void* newLabels = realloc(labelsList->labels_table, newSize); 
        if (newLabels == NULL) 
		{
			labels_table_dispose();
			printf(MEMORY_ALLOC_ERROR_IN("table.c -> insert_label(,,,) -> newLabels"));
            exit(1);
        } 
		else 
		{    
            labelsList->size = newSize;
            labelsList->labels_table = (label*)newLabels;
        }

    }

    labelsList->labels_table[nLabels]->label_name = (char *)malloc_with_check(strlen(label_name) + 1);
	if (labelsList->labels_table[nLabels]->label_name == NULL) 
	{
		labels_table_dispose();
		printf(MEMORY_ALLOC_ERROR_IN("table.c -> insert_label() -> label_name"));
		exit(1);
	} 
	strcpy(labelsList->labels_table[nLabels]->label_name, label_name);
	labelsList->labels_table[nLabels]->base = base;
	labelsList->labels_table[nLabels]->offset = offset;
	labelsList->labels_table[nLabels]->attribute[0] = (char *)malloc_with_check(strlen(attribute) + 1);
	if (labelsList->labels_table[nLabels]->attribute[0] == NULL) 
	{
		labels_table_dispose();
		printf(MEMORY_ALLOC_ERROR_IN("table.c -> insert_label() -> attribute[0]"));
		exit(1);
	} 
	strcpy(labelsList->labels_table[nLabels]->attribute[0], attribute);
    ++labelsList->nLabels;

    return True;
}

/**
 * @brief 
 * @return if the process is succeed
 */
bool add_entry_attribute(char *label_name)
{
	int i = 0;
	for(i = 0; i < labelsList->nLabels; i++)
	{
		if(strcmp(label_name, labelsList->labels_table[i]->label_name) == 0)
		{
			labelsList->labels_table[i]->attribute[1] = (char *)malloc_with_check(strlen(".entry") + 1);
			if (labelsList->labels_table[i]->attribute[1] == NULL) 
			{
				labels_table_dispose();
				printf(MEMORY_ALLOC_ERROR_IN("table.c -> add_entry_attribute() -> attribute[1]"));
				exit(1);
			} 
			strcpy(labelsList->labels_table[i]->attribute[1], ".entry");
			return True;
		}
	}
	printf(LABEL_NOT_FOUND_ADD_ENTRY(*label_name));
    return False;
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

static void labels_table_dispose()
{
	/* Labels section*/
	int i;
	for(i = 0; i < labelsList->nLabels; i++)
	{
		free(labelsList->labels_table[i]->label_name);
		free(labelsList->labels_table[i]->attribute[0]);
		free(labelsList->labels_table[i]->attribute[1]);
	}
    free(labelsList->labels_table);
    free(labelsList);
}


void tables_dispose()
{
	/* Labels section*/
    labels_table_dispose();
}
