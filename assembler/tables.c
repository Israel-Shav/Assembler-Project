#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "tables.h"
#include "errors.h"
#include "utils.h"

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
 * @return if action exist
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
 *  
 * 
 *  @brief Macros table section:
 * 
 */

static macros_list *macrosList;

/**
 * @brief 
 * @return if the process is succeed
 */
static bool init_macros_table();

/**
 * @brief 
 * @return if label_name is macro
 */
static void macros_table_dispose_node(macro_node* node);
static void macros_table_dispose();

/**
 * @brief 
 * @return if the process is succeed
 */
bool init_macros_table()
{
    macrosList = (macros_list *)malloc(sizeof(macros_list));
	macrosList->size = 0;
    return True;
}

/**
 * @brief 
 * @return if the process is succeed
 */
bool insert_macro(char *macro_name, char *new_line)
{
	macro_node* node;

	if(macrosList == NULL && !init_macros_table())
		return False;
	node = macrosList->head;
	if(node != NULL)
	{
		while(node->next != NULL)
		{
			if(strcmp(node->name ,macro_name) == 0)
			{
				node->data = (char *)realloc(node->data ,strlen(node->data) + strlen(new_line) + 1);
				if (node->data == NULL) 
				{
					macros_table_dispose();
					printf(MEMORY_ALLOC_ERROR_IN, "table.c -> insert_macro(,,,) -> node->data");
					exit(1);
				}
				strcat(node->name , new_line);
				return True;
			}
			node = node->next;
		}
		if(strcmp(node->name ,macro_name) == 0)
		{
			node->data = (char *)realloc(node->data ,strlen(node->data) + strlen(new_line) + 1);
			if (node->data == NULL) 
			{
				macros_table_dispose();
				printf(MEMORY_ALLOC_ERROR_IN, "table.c -> insert_macro(,,,) -> node->data");
				exit(1);
			}
			strcat(node->data , new_line);
			return True;
		}
		node = node->next = (macro_node *)malloc(sizeof(macro_node));
	}
	else
	{
		node = macrosList->head = (macro_node *)malloc(sizeof(macro_node));
	}
	if (node == NULL) 
	{
		macros_table_dispose();
		printf(MEMORY_ALLOC_ERROR_IN, "table.c -> insert_macro(,,,) -> node");
		exit(1);
	} 
	node->name = (char *)malloc(strlen(macro_name) + 1);
	if (node->name == NULL) 
	{
		macros_table_dispose();
		printf(MEMORY_ALLOC_ERROR_IN, "table.c -> insert_macro(,,,) -> node->name ");
		exit(1);
	}
	strcpy(node->name , macro_name);
	node->data = (char *)malloc(strlen(new_line) + 1);
	if (node->data == NULL) 
	{
		macros_table_dispose();
		printf(MEMORY_ALLOC_ERROR_IN, "table.c -> insert_macro(,,,) -> node->data");
		exit(1);
	}
	strcpy(node->data , new_line);
	(macrosList->size)++;
    return True;
}

/**
 * @brief 
 * @return Requested marco's code
 */
char *get_macro_code(char *macro_name)
{
	/* If not exist return NULL */
	macro_node* node;

	if(macrosList == NULL || macro_name == NULL)
		return NULL;

	node = macrosList->head;
	while(node != NULL)
	{
		if(strcmp(node->name ,macro_name) == 0)
		{
			return node->data;
		}
		node = node->next;
	}
    return NULL;
}

void print_macros_table()
{
	macro_node* node;
	if(macrosList == NULL)
		return;
	
	node = macrosList->head;
	printf("Macro\tdata\t\t\n");
	while(node != NULL)
	{
		printf("%s\t%s\t\t\n", node->name, node->data);
		node = node->next;
	}
}

static void macros_table_dispose_node(macro_node* node)
{
	if(node == NULL)
		return;
	macros_table_dispose_node(node->next);
	free(node->name);
	free(node->data);
	free(node);
}

static void macros_table_dispose()
{
	if(macrosList != NULL)
	{
		macros_table_dispose_node(macrosList->head);
		free(macrosList);
	}
}

/**
 *  
 * 
 *  @brief Labels table section:
 * 
 */

static labels_list *labelsList;

/**
 * @brief Static declartions: should be only in same file otherwise it will be copied
 * 
 */

/**
 * @brief 
 * @return if the process is succeed
 */
static bool init_labels_table();

/**
 * @brief 
 * @return if label_name is label
 */
static void labels_table_dispose_node(label_node* node);
static void labels_table_dispose();

/**
 * @brief 
 * @return if the process is succeed
 */
static bool init_labels_table()
{
	labelsList = (labels_list *)malloc(sizeof(labels_list));
	labelsList->size = 0;
    return True;
}

/**
 * @brief 
 * @return if the process is succeed
 */
bool insert_label(char *label_name, char *attribute, int base, int offset)
{
	unsigned int size;
	label_node* node;
	
	size = 1;
	if(labelsList == NULL && !init_labels_table())
		return False;
	node = labelsList->head;
	if(node == NULL)
		node = labelsList->head = (label_node *)malloc(sizeof(label_node));
	else
	{
		while(node->next != NULL)
		{
			size++;
			node = node->next;
		}
		node = node->next = (label_node *)malloc(sizeof(label_node));
	}
	if (node == NULL) 
	{
		labels_table_dispose();
		printf(MEMORY_ALLOC_ERROR_IN, "table.c -> insert_label(,,,) -> node");
		exit(1);
	} 
	node->label_name = (char *)malloc_with_check(strlen(label_name) + 1);
	if (node->label_name == NULL) 
	{
		labels_table_dispose();
		printf(MEMORY_ALLOC_ERROR_IN, "table.c -> insert_label() -> node->label_name");
		exit(1);
	} 
	strcpy(node->label_name, label_name);
	node->base = base;
	node->offset = offset;
	node->attribute[0] = (char *)malloc_with_check(strlen(attribute) + 1);
	if (node->attribute[0] == NULL) 
	{
		labels_table_dispose();
		printf(MEMORY_ALLOC_ERROR_IN, "table.c -> insert_label() -> node->attribute[0]");
		exit(1);
	} 
	strcpy(node->attribute[0], attribute);
	node->attribute[1] = NULL;
	node->next = NULL;
	labelsList->size = size;
    return True;
}

/**
 * @brief 
 * @return if the process is succeed
 */
bool add_entry_attribute(char *label_name)
{
	label_node* node;
	node = labelsList->head;
	while(node != NULL)
	{
		if(strcmp(label_name, node->label_name) == 0)
		{
			node->attribute[1] = (char *)malloc_with_check(strlen(".entry") + 1);
			if (node->attribute[1] == NULL) 
			{
				labels_table_dispose();
				printf(MEMORY_ALLOC_ERROR_IN, "table.c -> add_entry_attribute() -> attribute[1]");
				exit(1);
			} 
			strcpy(node->attribute[1], ".entry");
			return True;
		}
		node = node->next;
	}
	printf(LABEL_NOT_FOUND_ADD_ENTRY, label_name);
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

/**
 * @brief 
 * @return if label_name is label
 */
static void labels_table_dispose_node(label_node* node)
{
	if(node == NULL)
		return;
	labels_table_dispose_node(node->next);
	free(node->label_name);
	free(node->attribute[0]);
	free(node->attribute[1]);
	free(node);
}

static void labels_table_dispose()
{
	if(labelsList != NULL)
	{
		labels_table_dispose_node(labelsList->head);
		free(labelsList);
	}
}

void print_label_table()
{
	label_node* node;
	if(labelsList == NULL)
		return;
	
	node = labelsList->head;
	printf("Label\tbase\toffset\tattributes #1, #2\t\t\n");
	while(node != NULL)
	{
		printf("%s\t%d\t%d\t%s, %s\t\n", node->label_name, node->base, node->offset, node->attribute[0], node->attribute[1]);
		node = node->next;
	}
}

/**
 * @brief 
 * @return if label_name is label
 */
void tables_dispose()
{
	/* Labels section*/
	macros_table_dispose();
    labels_table_dispose();
}
