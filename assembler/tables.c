#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "globals.h"
#include "storage.h"
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

static labels_list *labelsList, *externalLabelsList;

/**
 * @brief Static declartions: should be only in same file otherwise it will be copied
 * 
 */

/**
 * @brief 
 * 
 * @param label_name 
 * @return true 
 * @return false 
 */
static bool is_label_external(char *label_name);

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
	labelsList->head = NULL;
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
static bool init_external_labels_table();

/**
 * @brief 
 * @return if label_name is label
 */
static void external_labels_table_dispose_node(label_node* node);

/**
 * @brief 
 * @return if the process is succeed
 */
static bool init_external_labels_table()
{
	externalLabelsList = (labels_list *)malloc(sizeof(labels_list));
	externalLabelsList->size = 0;
	externalLabelsList->head = NULL;
    return True;
}

/**
 * @brief 
 * @return if the process is succeed
 */
void insert_external_label(char *label_name, int base, int offset)
{
	unsigned int size;
	label_node* node;

	if(!is_label_external(label_name))
		return;

	size = 1;
	if(externalLabelsList == NULL && !init_external_labels_table())
		return;
	node = externalLabelsList->head;
	if(node == NULL)
		node = externalLabelsList->head = (label_node *)malloc(sizeof(label_node));
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
		printf(MEMORY_ALLOC_ERROR_IN, "table.c -> insert_external_label(,,,) -> node");
		exit(1);
	} 
	node->label_name = (char *)malloc_with_check(strlen(label_name) + 1);
	if (node->label_name == NULL) 
	{
		labels_table_dispose();
		printf(MEMORY_ALLOC_ERROR_IN, "table.c -> insert_external_label() -> node->label_name");
		exit(1);
	} 
	strcpy(node->label_name, label_name);
	node->base = base;
	node->offset = offset;
	node->attribute[0] = NULL;
	node->attribute[1] = NULL;
	node->next = NULL;
	externalLabelsList->size = size;
}

/**
 * @brief 
 * 
 * @param label_name 
 * @return true 
 * @return false 
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
 * 
 * @param icf 
 * @return true 
 * @return false 
 */
bool after_first_phase_update(int icf)
{
	label_node* node;
	int new_place;
	node = labelsList->head;
	while(node != NULL)
	{
		if(node->attribute[0] && strcmp(".data", node->attribute[0]) == 0)
		{
			new_place = node->base + node->offset + icf;
			node->offset = new_place % 16;
			node->base = new_place - node->offset;
		}
		node = node->next;
	}
    return True;
}

/**
 * @brief 
 * 
 * @param label_name 
 * @return true 
 * @return false 
 */
bool is_label_exist(char *label_name)
{
	label_node* node;

	if(labelsList == NULL && !init_labels_table())
		return False;
	
	node = labelsList->head;
	while(node != NULL)
	{
		if(label_name && strcmp(label_name, node->label_name) == 0)
			return True;
		node = node->next;
	}
    return False;
}

/**
 * @brief 
 * 
 * @param label_name 
 * @return true 
 * @return false 
 */
static bool is_label_external(char *label_name)
{
	label_node* node;

	if(labelsList == NULL)
		return False;
	
	node = labelsList->head;
	while(node != NULL)
	{
		if(label_name && strcmp(label_name, node->label_name) == 0 && node->attribute[0] != NULL && strcmp(".extern", node->attribute[0]) == 0)
			return True;
		node = node->next;
	}
    return False;
}

/**
 * @brief Get the label object
 * 
 * @param label_name 
 * @return label_node* 
 */
label_node *get_label(char *label_name)
{
	label_node* node;

	if(labelsList == NULL || label_name == NULL)
		return NULL;
	
	node = labelsList->head;
	while(node != NULL)
	{
		if(label_name && strcmp(label_name, node->label_name) == 0)
			return node;
		node = node->next;
	}
    return NULL;
}

/**
 * @brief 
 * 
 * @param label_name 
 * @return true 
 * @return false 
 */
bool is_valid_label_name(char *label_name)
{
	int i;
	if(label_name == NULL || is_register(label_name) != NONE_REG || is_action_exist(label_name) || 
	 (strlen(label_name) != 0 && !isalpha(label_name[0])))
		return False;
	for (i = 1; i <= MAX_LABEL_LEN && label_name[i] != STRING_END ; i++)
		if(!isalnum(label_name[i]))
			return False;
	if(i == MAX_LABEL_LEN && label_name[i] != STRING_END)
		return False;
	return True;
}


/**
 * @brief 
 * 
 * @param label_name 
 * @return true 
 * @return false 
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
 * @brief Create a entries file object
 * 
 * @param new_filename 
 */
void create_entries_file(char *new_filename)
{
	label_node* node;
	FILE *entries_file;
	if(labelsList == NULL)
		return;
	
	entries_file = NULL;
	node = labelsList->head;
	while(node != NULL)
	{

		if(node->attribute[1] != NULL && strcmp(".entry", node->attribute[1]) == 0)
		{
			/* Open file, skip on failure, current assembly file descriptor to process */
			if(entries_file == NULL)
			{
				entries_file = fopen(new_filename, WRITE_PERMISSIONS);
				if (entries_file == NULL) 
				{
					/* if file couldn't be opened, write to stderr. */
					printf(WRITING_PERMISSIONS_ERROR, new_filename);
					return;
				}
			}
			fprintf(entries_file, "%s,%d,%d\n", node->label_name, node->base, node->offset);
		}
		node = node->next;
	}
}

/**
 * @brief Create a externals file object
 * 
 * @param new_filename 
 */
void create_externals_file(char *new_filename)
{
    label_node* node;
	FILE *externals_file;
	if(externalLabelsList == NULL)
		return;
	
	externals_file = NULL;
	node = externalLabelsList->head;
	while(node != NULL)
	{
		/* Open file, skip on failure, current assembly file descriptor to process */
		if(externals_file == NULL)
		{
			externals_file = fopen(new_filename, WRITE_PERMISSIONS);
			if (externals_file == NULL) 
			{
				/* if file couldn't be opened, write to stderr. */
				printf(WRITING_PERMISSIONS_ERROR, new_filename);
				return;
			}
		}
		fprintf(externals_file, "%s BASE %.4d\n", node->label_name, node->base);
		fprintf(externals_file, "%s OFFSET %.4d\n\n", node->label_name, node->offset);
		node = node->next;
	}
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

/**
 * @brief 
 * @return if label_name is label
 */
static void external_labels_table_dispose_node(label_node* node)
{
	if(node == NULL)
		return;
	external_labels_table_dispose_node(node->next);
	free(node->label_name);
	free(node);
}

static void labels_table_dispose()
{
	if(labelsList != NULL)
	{
		labels_table_dispose_node(labelsList->head);
		free(labelsList);
	}
	if(externalLabelsList != NULL)
	{
		external_labels_table_dispose_node(externalLabelsList->head);
		free(externalLabelsList);
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
