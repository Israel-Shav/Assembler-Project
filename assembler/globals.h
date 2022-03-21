/**
 * @brief Constants:
 */

/* Maximum length of a single source line, exclude \n and \0  */
#define MAX_LINE_LENGTH 80

#define TOKENS_DELIMITERS "\n\t\r "

#define TOKENS_DELIMITERS_COLON "\n\t\r :"

#define TOKENS_DELIMITERS_WO_SPACE "\n\t\r"

#define COMMENT ';'

#define COMMA ','

#define QUOTE '"'

#define TAB '\t'

#define STRING_END '\0'

#define SPACE ' '

#define NEW_LINE '\n'

#define NEW_LINE_STR "\n"

#define NEW_LINE_DELIMITERS "\r" NEW_LINE_STR

#define READ_PERMISSIONS "r"

#define WRITE_PERMISSIONS "w"

#define TOKENS_DELIMITERS_COMMA "\n\t\r ,"

/**
 * @brief Prototypes:
 */

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


/* bool definition */
typedef enum booleans {
	False = 0,
    True = 1
} bool;


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
} action_element;
