# Assembler project:

## About
This project is an aslabelment in a C programming course at the open unvieristy (20465). The purpose of this project is to build an assembler for 15-instruction asssembly language, for an imaginary 16-bit CPU and 20 bits of memory size.
This project was done by [@Israel-Shav](//github.com/Israel-Shav) and [@roei2344](//github.com/roei2344).
For any issues, questions and ideas turn to the Issues tab.

## Usage
`./assembler file1 file2 file3 ...` Will start the processing of each file (specify WITHOUT extension!). No support for double-quoting file names.

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
    (*) static macro_line_process(char *line, bool *is_macro_block, char *macro_name, FILE* new_file) -> bool

### first_phase.c:
    (*) first_phase_process(*after_macro_phase_source_file) -> bool:
        1) Define and aslabel variables like is_success = True
        2) tables.c -> init_labels_table().
        3) Read line from *after_macro_phase_source_file. If end of file, got to (4).
            a) Define and aslabel variables like current_label = NULL, is_label = False.
            b) If first operand is Label:
                1) is_label = True
                2) As label current_label
            c) If data instruction (.data or .string):
                1) Encode data into storage. storage.c -> encode_data(attribute, data[0], data[1], ...) -> [base, offset]
                2) If is_label == True:
                    a) Insert this Label to labels table with .data attribute. tables.c -> insert_label(current_label, attribute = data, base, offset) -> returns bool.
                4) Return to (3)
            d) If linked instruction (.entry or .extern):
                1) If .entry: return to (3). [It will be considered in second phase].
                2) If .extern: 
                    a) Insert operand as Label with base=0 and offset=0. tables.c -> insert_label(current_label = operand, attribute = external, base = 0, offset = 0) -> returns bool.
                    b) Return to (3)
            e) This is instruction, so if first operand is Label:
                1) tables.c -> insert_label(current_label, attribute = code, base, offset) -> returns bool.
            f) Search for function in functions table. tables.c -> is_func_exist(func_name) -> returns bool.
            g) Encode instruction into storage. storage.c -> first_encode_instruction(instruction[0], instruction[1], ...) -> {}
            h) returns to (3)
        4) If errors found, *STOP-HERE* and return is_success -> bool.

### second_phase.c:
    (*) second_phase_process(after_macro_phase_source_file, is_success) -> bool:
        0.5) ICF, DCF, data labels update. storage.c -> pre_second_phase_data_update() -> bool
        1) Read line from after_macro_phase_source_file. If end of file, got to (2).
            a) If first operand is Label, skip it to next operand.
            b) If operand is .extern, .string, .data: return to (1).
            c) If operand is .entry:
                1) Add attribute=entry to label_table. tables.c -> update_entry(label_name) -> bool.
                2) Return to (1).
            d) Finish encoding info-words.storage.c -> second_encode_instruction(instruction[0], instruction[1], ...) -> {}
        2) Return bool.

### storage.c:
    (**) static DC = 0, IC = 100, DCF, ICF, data_storage, code_storage
    (*) init_storage() -> bool:
        1) Initialize each structure and simple data types.
    (*) encode_data(attribute, data_len, ...) -> bool:
        1) Determine if .data or .string.
        2) Encode data into data_storage by previous information.
        3) DC += L (L - number of words added to data_storage)
    (*) first_encode_instruction(*instruction) -> bool:
        1) Analyze operands structure and calculate number of words that will be in code_storage (number of words will called L, get addressing mode, etc.)
        2) Encode instruction data into code_storage by previous information.
        3) IC += L (L - number of words added to code_storage)
        4) Returns {}.
    (*) second_encode_instruction(*instruction*) -> bool:
        1) Check out page 37, second pass, section 6.
    (*) pre_second_phase_data_update() -> bool:
        1) Update ICF and DCF. [Will be used after second_phase].
        2) Update base and east for each data label in labels_table.
    (*) storage_dispose() -> void.

### output_producer.c:
    (*) build_output_files(filename) -> bool

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

### utils.c:
    (*) get_line_info(*file_path) -> line_info
    (*) getFileName(*path) -> char*
    (*) ifFileExist(*filename) -> bool

### globals.h:
    (***) typedef struct line_info: label, func, operands
    (***) 