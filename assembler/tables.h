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
 *  @brief Actions table section:
 * 
 */

/**
 * @brief 
 * @return if action exist
 */
bool is_action_exist(char *action_name);

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

/* Commands opcode */
typedef enum opcodes {
	/* First Group */
	MOV_OP = 0,
	CMP_OP = 1,
	ADD_OP = 2,
	SUB_OP = 2,
	LEA_OP = 4,

	/* Second Group */
	CLR_OP = 5,
	NOT_OP = 5,
	INC_OP = 5,
	DEC_OP = 5,
	JMP_OP = 9,
	BNE_OP = 9,
	JSR_OP = 9,
	RED_OP = 12,
	PRN_OP = 13,

	/* Third Group */
	RTS_OP = 14,
	STOP_OP = 15,

	/* Error */
	NONE_OP = -1
} opcode;

/* Commands funct */
typedef enum functs {
	/* opcode 2 */
	ADD_FUNCT = 10,
	SUB_FUNCT = 11,

	/* opcode 5 */
	CLR_FUNCT = 10,
	NOT_FUNCT = 11,
	INC_FUNCT = 12,
	DEC_FUNCT = 13,

	/* opcode 9 */
	JMP_FUNCT = 10,
	BNE_FUNCT = 11,
	JSR_FUNCT = 12,

	/* Error */
	NONE_FUNCT = 0
} funct;

/* Registers */
typedef enum registers {
	R0 = 0,
	R1,
	R2,
	R3,
	R4,
	R5,
	R6,
	R7,
    R8,
    R9,
    R10,
    R11,
    R12,
    R13,
    R14,
    R15,
	NONE_REG = -1
} reg;

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

/* Represents label object */
typedef struct label {
	/* Name of label */
	char *label_name;
	/* Base */
	int base;
    /* Offset */
	int offset;
    /* Attributes */
	char *attribute[2];
} label;

typedef struct labels_list {
	label *labels_table;
	unsigned int nLabels;
	unsigned int size;
	unsigned int block_size;
} labels_list;

typedef struct action_element {
    /* Name of action */
	char *action;
    /* Action's opcode */
	opcode op;
    /* Action's funct */
	funct fun;
} action_element;
