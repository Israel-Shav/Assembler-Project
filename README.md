# Assembler project:

## About
This project is an assignment in a C programming course at the open unvieristy (20465). The purpose of this project is to build an assembler for 15-instruction asssembly language, for an imaginary 16-bit CPU and 20 bits of memory size.
This project was done by [@Israel-Shav](//github.com/Israel-Shav) and [@roei2344](//github.com/roei2344).
For any issues, questions and ideas turn to the Issues tab.

## Project structure:
    Modules:
        assembler c
        first_phase c h
        second_phase c h
        utils c h
        globals h
        table c h
        pre_assembler c h
        storge c h
        output_stream c h

### assembler.c:
    (*) main:
        1) Proccess every file from args
        2) For each file:
            a) Define and assgin variables like is_success = True. storge.c -> storge_init()
            b) pre_assembler phase. pre_assembler.c -> macro_phase_process(*source_file) -> returns *FILE.
            c) is_success = First phase. first_phase.c -> first_phase_process(*new_source_file_path) -> bool
            d) is_success = is_success && Second phase. second_phase.c -> second_phase_process(*new_source_file_path, is_success) -> bool
            e) If is_success == True: build output files. output_stream.c -> build_output_files() -> bool
            f) Else: erros output

### pre_assembler.c:
    (*) macro_phase_process(*source_file) -> return bool: 
        1) Define and assign variables like macro_table. table.c -> init_macro_table()
        2) Copy file to New file (will be source file after macro spreading). utils.c -> copyFile(file_name) -> returns new file path.
        3) define is_in_macro_block = False, macro_name = NULL.
        4) Read line from NEW source file. If end of file, go to (5).
            a) If is_macro_stream == True:
                1) If first field is "endm":
                    a) is_macro_stream = False, macro_name = NULL.
                2) Else:
                    a) Insert line to macro_table. table.c -> insert_macro(macro_name, line) -> returns bool.
                3) Delete line from new source file.
            b) Go to (4).
        5) Read line from begining of NEW source file. If end of file go to (6).
            b) If first field is a macro that appear in macro_table:
                1) Replace it with macro conent from macro_table. table.c -> get_macro_code(macro_name) -> *char
                2) Return to (5).
        6) Free macro_table. table.c -> free_macro_table() -> return bool.
        7) return new_source_file_pnt -> *FILE.

### first_phase.c:
    (*) first_phase_process(*after_macro_phase_source_file) -> bool:
        1) Define and assign variables like is_success = True
        2) table.c -> init_signs_table().
        3) Read line from *after_macro_phase_source_file. If end of file, got to (4).
            a) Define and assign variables like current_label = NULL, is_label = False.
            b) If first operand is Label:
                1) is_label = True
                2) Assign current_label
            c) If data instruction (.data or .string):
                1) Encode data into storge. storge.c -> encode_data(attribute, data[0], data[1], ...) -> [base, offset]
                2) If is_label == True:
                    a) Insert this Label to signs table with .data attribute. table.c -> insert_sign(current_label, attribute = data, base, offset) -> returns bool.
                4) Return to (3)
            d) If linked instruction (.entry or .extern):
                1) If .entry: return to (3). [It will be considered in second phase].
                2) If .extern: 
                    a) Insert operand as Label with base=0 and offset=0. table.c -> insert_sign(current_label = operand, attribute = external, base = 0, offset = 0) -> returns bool.
                    b) Return to (3)
            e) This is instruction, so if first operand is Label:
                1) table.c -> insert_sign(current_label, attribute = code, base, offset) -> returns bool.
            f) Search for function in functions table. table.c -> is_func_exist(func_name) -> returns bool.
            g) Encode instruction into storge. storge.c -> first_encode_instruction(instruction[0], instruction[1], ...) -> {}
            h) returns to (3)
        4) If errors found, *STOP-HERE* and return is_success -> bool.
        5) ICF, DCF, data signs update. storge.c -> pre_second_phase_data_update() -> bool

### second_phase.c:
    (*) second_phase_process(after_macro_phase_source_file, is_success) -> bool:
        1) Read line from after_macro_phase_source_file. If end of file, got to (2).
            a) If first operand is Label, skip it to next operand.
            b) If operand is .extern, .string, .data: return to (1).
            c) If operand is .entry:
                1) Add attribute=entry to sign_table. table.c -> update_entry(label_name) -> bool.
                2) Return to (1).
            d) Finish encoding info-words.storge.c -> second_encode_instruction(instruction[0], instruction[1], ...) -> {}
        2) Return bool.

### storge.c:
    (**) static DC = 0, IC = 100, DCF, ICF, data_storge, code_storge
    (*) storge_init() -> bool:
        1) Initialize each structure and simple data types.
    (*) encode_data(attribute, data_len, ...) -> bool:
        1) Determine if .data or .string.
        2) Encode data into data_storge by previous information.
        3) DC += L (L - number of words added to data_storge)
    (*) first_encode_instruction(data_len, ...) -> {}:
        1) Analyze operands structure and calculate number of words that will be in code_storge (number of words will called L, get addressing mode, etc.)
        2) Encode instruction data into code_storge by previous information.
        3) IC += L (L - number of words added to code_storge)
        4) Returns {}.
    (*) second_encode_instruction(data_len, ...) -> {}:
        1) Check out page 37, second pass, section 6.
    (*) pre_second_phase_data_update() -> bool:
        1) Update ICF and DCF. [Will be used after second_phase].
        2) Update base and east for each data sign in signs_table.

### output_stream.c:
    (*) build_output_files(file_name) -> bool

### table.c:
    (**) funcs_table, macros_table, signs_table, registers_table
    (*) init_macro_table() -> bool.
    (*) insert_macro(macro_name, line) -> returns bool.
    (*) get_macro_code(macro_name) -> *char.
    (*) init_signs_table() -> bool.
    (*) insert_sign(current_label, attribute, base, offset) -> returns bool.
    (*) is_func_exist(func_name) -> returns bool.
    (*) update_entry(label_name) -> bool.

### utils.c:
    (*) get_line_info(file_path) -> line_info
    (*) copyFile(file_name) -> returns new file path

### globals.h:
    (***) typedef struct line_info: label, func, operands
    (***) 