/**
 * @brief Enums:
 */

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



/**
 * @brief Structs:
 */

typedef struct action_element {
    /* Name of action */
	char *action;
    /* Action's opcode */
	opcode op;
    /* Action's funct */
	funct fun;
	/* Operands count */
	int opCount;
	/* id */
	unsigned int id;
} action_element;

/* Represents a single opcode word */
typedef struct opcode_word {
	unsigned int opcode: 16;
	unsigned int ERA: 3;
    unsigned int END: 1;
} opcode_word;

/* Represents a single code word */
typedef struct code_word {
    unsigned int dest_addressing: 2;
    unsigned int dest_register: 4;
    unsigned int src_addressing: 2;
    unsigned int src_register: 4;
    unsigned int funct: 4;
	unsigned int ERA: 3;
    unsigned int END: 1;
} code_word;

/* Represents a single data word. */
typedef struct data_word {
 	int data: 16;
	unsigned int ERA: 3;
    unsigned int END: 1;
} data_word;

/* Represents a single object word. */
typedef struct object_word {
	unsigned int E: 4;
	unsigned int D: 4;
 	unsigned int C: 4;
	unsigned int B: 4;
    unsigned int A: 4;
} object_word;

/* Represents a general machine code word contents */
typedef struct machine_word {
	/* if it represents code (not additional data), this field contains the total length required by the code. if it's data, this field is 0. */
	short length;
	/* The content can be code or data */
	union word {
        opcode_word *opcode;
		data_word   *data;
		code_word   *code;
		object_word	*object;
	} word;
} machine_word;

/**
 * @brief Constants:
 */

#define MEMORY_CAPACITY 8192

#define MAX_DATA_WORD_SIZE 16

#define DEFAULT_DC 0

#define DEFAULT_IC 100

#define DEFAULT_IC_DC_FINAL -1

/**
 * @brief Prototypes:
 */


/**
 * @brief 
 * @return if action exist
 */
bool is_action_exist(char *action_name);

/**
 * @brief 
 * @return if action exist
 */
action_element *get_action(char *action_name);

/**
 * @brief 
 * 
 * @param register_name 
 * @return reg 
 */
reg is_register(char *register_name);

/**
 * @brief 
 * @return if the process is succeed
 */
bool init_storage();


/**
 * @brief 
 * @return if the process is succeed
 */
bool encode_data(char *attribute, char *data, char *filename, int line_number);

/**
 * @brief 
 * @return if the process is succeed
 */
bool first_encode_instruction(char *action, char *operands, char *filename, int line_number);
/**
 * @brief 
 * @return if the process is succeed
 */
bool second_encode_instruction(char *action, char *operands, char *filename, int line_number);

/**
 * @brief 
 * @return if the process is succeed
 */
bool pre_second_phase_data_update();

/**
 * @brief 
 * @return dc VALUE
 */
int get_dc();

/**
 * @brief Create a object file object
 * 
 * @param new_filename 
 */
void create_object_file(char *new_filename);

/**
 * @brief 
 */
void storage_dispose();


void print_storage_table();

