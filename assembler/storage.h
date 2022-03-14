/**
 * @brief Constants:
 */

/**
 * @brief Prototypes:
 */

/**
 * @brief 
 * @return if the process is succeed
 */
bool init_storage();

/**
 * @brief 
 * @return if the process is succeed
 */
bool encode_data(char *attribute, char *data);

/**
 * @brief 
 * @return if the process is succeed
 */
bool first_encode_instruction(char *action, char *operands);
/**
 * @brief 
 * @return if the process is succeed
 */
bool second_encode_instruction(char *action, char *operands);

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
 * @brief 
 */
void storage_dispose();

/**
 * @brief Enums:
 */

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
	unsigned int data: 16;
	unsigned int ERA: 3;
    unsigned int END: 1;
} data_word;

/* Represents a general machine code word contents */
typedef struct machine_word {
	/* if it represents code (not additional data), this field contains the total length required by the code. if it's data, this field is 0. */
	short length;
	/* The content can be code or data */
	union word {
        opcode_word *opcode;
		data_word   *data;
		code_word   *code;
	} word;
} machine_word;