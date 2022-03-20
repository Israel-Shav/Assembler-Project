/**
 * @brief Constants:
 */

#define MAX_LABEL_LEN 31

/**
 * @brief Prototypes:
 */


/**
 *  
 * 
 *  @brief Instructions table section:
 * 
 */


/**
 * @brief 
 * @return if label_name is label
 */
bool is_data_instruction(char *instruction_word);

/**
 * @brief 
 * @return if instruction_word is .extern or .entry
 */
bool is_linked_instruction(char *instruction_word);


/**
 *  
 * 
 *  @brief Macros table section:
 * 
 */

/**
 * @brief 
 * @return if the process is succeed
 */
bool init_macro_table();

/**
 * @brief 
 * @return if the process is succeed
 */
bool insert_macro(char *macro_name, char *new_line);

/**
 * @brief 
 * @return Requested marco's code
 */
char *get_macro_code(char *macro_name);

void print_macros_table();

/**
 *  
 * 
 *  @brief Labels table section:
 * 
 */

/**
 * @brief 
 * @return if the process is succeed
 */
bool insert_label(char *label_name, char *attribute, int base, int offset);

/**
 * @brief 
 * @return if the process is succeed
 */
bool add_entry_attribute(char *label_name);

/**
 * @brief 
 * @return if label_name is label
 */
bool is_label(char *label_name);

/**
 * @brief 
 */
void tables_dispose();

void print_label_table();

/**
 * @brief Enums:
 */

/* Instructions*/
/* typedef enum instruction {
	DATA_INST,
	EXTERN_INST,
	ENTRY_INST,
	STRING_INST,
	NONE_INST,
	ERROR_INST
} instruction; */

/**
 * @brief Structs:
 */

/* Represents macro object */
typedef struct macro {
	/* Name of macro */
	char *name;
	/* Macro's data */
	char *data;
} macro;

/* Represents macro object */
typedef struct macro_node {
	/* Name of macro */
	char *name;
	/* Macro's data */
	char *data;
	/* Next */
	struct macro_node *next;
} macro_node;

typedef struct macros_list {
	macro_node *head;
	unsigned int size;
} macros_list;

/* Represents label object */
typedef struct label_node {
	/* Name of label */
	char *label_name;
	/* Base */
	int base;
    /* Offset */
	int offset;
    /* Attributes */
	char *attribute[2];
	/* Next */
	struct label_node *next;
} label_node;

typedef struct labels_list {
	label_node *head;
	unsigned int size;
} labels_list;

