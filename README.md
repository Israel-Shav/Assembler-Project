# Assembler project:

## About
This project is an aslabelment in a C programming course at the open unvieristy (20465). The purpose of this project is to build an assembler for 16-instruction asssembly language, for an imaginary 16-bit CPU and 16 bits of memory size.
This project was done by [@Israel-Shav](//github.com/Israel-Shav) and [@roei2344](//github.com/roei2344).
For any issues, questions and ideas turn to the Issues tab.

## Usage
1) cd ./assembler
2) make
3) `./assembler file1 file2 file3 ...` Will start the processing of each file (specify WITHOUT extension!). No support for double-quoting file names.
4) For debug mode please add -d or --debug to arguments

## Project structure:
    Modules:
        assembler c h
        globals h
        errors h
        first_phase c h
        second_phase c h
        utils c h
        tables c h
        pre_assembler c h
        storage c h
        output_producer c h

### assembler.c:
    (*) main(int argc, char *argv[]) -> int
    (*) static process_file(char *filename) -> bool

### pre_assembler.c:
    (*) macro_phase_process(char *filename) -> char*
    (*) static *macro_line_process(char *line, bool *is_process_stable, char *macro_name, FILE* new_file) -> char*

### first_phase.c:
    (*) first_phase_process(char *full_filename) -> bool
    (*) static fp_line_process(char *line, bool *is_process_stable, char *filename, int line_number) -> bool

### second_phase.c:
    (*) second_phase_process(char *full_filename) -> bool
    (*) static sp_line_process(char *line, bool *is_process_stable, char *filename, int line_number) -> bool

### storage.c:
    (**) static DC = 0, IC = 100, DCF, ICF, data_storage, code_storage
    (**) static struct action_element op_fuct_table[]
    (*) init_storage() -> bool
    (*) storage_dispose() -> void.
    (*) print_storage_table() -> voif
    (*) print_bits(int decimal, unsigned int bit_size) -> void
    (*) is_action_exist(char *action_name) -> bool
    (*) get_action(char *action_name) -> action_element*
    (*) is_register(char *register_name) -> reg
    (*) encode_data(char *attribute, char *data, char *filename, int line_number) -> bool
    (*) static first_phase_opreand_update(char *operand, code_word *codeWord, bool is_first_operand) -> bool
    (*) first_encode_instruction(char *action, char *operands, char *filename, int line_number) -> bool
    (*) pre_second_phase_data_update() -> bool
    (*) second_encode_instruction(char *action, char *operands, char *filename, int line_number) -> bool
    (*) static second_phase_word_update(char *word_name) -> void
    (*) pre_second_phase_data_update() -> bool
    (*) get_dc() -> int
    (*) get_ic() -> int
    (*) create_object_file(char *new_filename) -> void


### output_producer.c:
    (*) build_output_files(char *filename, bool debug_mode) -> bool

### tables.c:
    (**) funcs_table, macros_table, labels_table, registers_table
    (*) init_macro_table() -> bool.
    (*) insert_macro(macro_name, line) -> bool.
    (*) get_macro_code(macro_name) -> *char.
    (*) init_labels_table() -> bool.
    (*) insert_label(current_label, attribute, base, offset) -> bool.
    (*) is_action_exist(func_name) -> bool.
    (*) add_entry_attribute(label_name) -> bool.
    (*) tables_dispose() -> void.
    (*) is_linked_instruction(char *instruction_word) -> bool
    (*) is_data_instruction(char *instruction_word) -> bool

### utils.c:
    (*) get_line_info(*file_path) -> line_info
    (*) getFileName(*path) -> char*
    (*) ifFileExist(*filename) -> bool

### globals.h:
    (***) typedef struct line_info: label, func, operands