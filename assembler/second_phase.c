// ic = IC_INIT_VALUE;

// 	/* Now let's add IC to each DC for each of the data symbols in table (step 1.19) */
// 	add_value_to_type(symbol_table, icf, DATA_SYMBOL);

// 	/* First pass done right. start second pass: */
// 	rewind(file_des); /* Start from beginning of file again */

// 	for (curr_line_info.line_number = 1; !feof(file_des); curr_line_info.line_number++) {
// 		int i = 0;
// 		fgets(temp_line, MAX_LINE_LENGTH, file_des); /* Get line */
// 		MOVE_TO_NOT_WHITE(temp_line, i)
// 		if (code_img[ic - IC_INIT_VALUE] != NULL || temp_line[i] == '.')
// 			process_status &= process_line_spass(curr_line_info, &ic, code_img, &symbol_table);
// 	}

// 		/* Write files if second pass succeeded */
// 		if (process_status) {
// 			/* Everything was done. Write to *filename.ob/.ext/.ent */
// 			process_status = write_output_files(code_img, data_img, icf, dcf, filename, symbol_table);
// 		}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "second_phase.h"
#include "errors.h"
#include "tables.h"
#include "storage.h"
#include "utils.h"


/**
 * @brief Allocates and builds the data inside the machine words storge by the given operand
 * @param full_filename The current code image
 * @return Whether succeeded.
 */
bool second_phase_process(char *full_filename)
{
	/* Declarations */
	FILE *file_des;
	char temp_line[MAX_LINE_LENGTH + 2], temp_c;
	bool is_process_stable;
	int line_number;

    /* Open file, skip on failure, current assembly file descriptor to process */
	file_des = fopen(full_filename, READ_PERMISSIONS);
	if (file_des == NULL) 
	{
		/* if file couldn't be opened, write to stderr. */
		printf(READING_PERMISSIONS_ERROR(full_filename));
		return False;
	}
	
	/* Read line - stop if read failed (when NULL returned) - usually when EOF. increase line counter for error printing. */
	for (line_number = 1, is_process_stable = True; fgets(temp_line, MAX_LINE_LENGTH + 2, file_des) != NULL; line_number++) 
	{
		/* if line too long, the buffer doesn't include the NEW_LINE='\n' char and the file isn't on end. */
		if (strchr(temp_line, NEW_LINE) == NULL && !feof(file_des))
		{
			/* Print message and prevent further line processing, as well as second pass.  */
			fprintf(ERR_OUTPUT_FILE, TOO_LONG_INPUT_LINE(full_filename, line_number, MAX_LINE_LENGTH));
			is_process_stable = False;
			/* skip leftovers */
			do 
			{
				temp_c = fgetc(file_des);
			} 
			while (temp_c != NEW_LINE && temp_c != EOF);
		} 
		else 
		{
			if (!fp_line_process(temp_line, &is_process_stable, full_filename, line_number) && is_process_stable)
				is_process_stable = False;
		}
	}
	fclose(file_des);
	return is_process_stable;
}

/**
 * @brief Processes a single line in the second phase
 * @param line The line text
 * @param bool Indicates if process stable
 * @return Whether succeeded.
 */
static bool sp_line_process(char *line, bool *is_process_stable, char *filename, int line_number)
{
	
	char *token, *current_label, *copy_line, *rest_of_str, *attribute;
	bool is_labeled;
	current_label = NULL;
	copy_line = (char *)malloc_with_check(strlen(line) + 1);
	is_labeled = False;
	strcpy(copy_line, line);

	/* Get the first token */
	token = strtok(line, TOKENS_DELIMITERS);
	if( token == NULL || strcmp(token, "") == 0 || (char)(token[0]) == COMMENT) 
	{
		free(copy_line);
		return True;
	}
	
	if((is_labeled = is_label(token)))
	{
		current_label = token;
		/* Get second token */
		token = strtok(NULL, TOKENS_DELIMITERS);
		if( token == NULL ) 
		{
			printf(EMPTY_LABEL_LINE(filename, line_number, copy_line));
			free(copy_line);
			return False;
		}
	}

	if(strcmp(token, ".entry") == 0)
	{
		attribute = token;
		rest_of_str = strtok(NULL, NEW_LINE_STR);
		if(rest_of_str == NULL)
		{
			printf(EMPTY_EXTERN_LINE(filename, line_number, copy_line));
			free(copy_line);
			return False;
		}
		if(*is_process_stable)
			*is_process_stable = add_entry_attribute(rest_of_str);
	}
	else if(is_action_exist(token))
	{
		rest_of_str = strtok(NULL, NEW_LINE_STR);
		if(*is_process_stable)
			*is_process_stable = second_encode_instruction(token, rest_of_str);
	}
	else
	{
		printf(UNKOWN_INSTRUCTION(filename, line_number, copy_line));
		free(copy_line);
		return False;
	}
	free(copy_line);
	return True;
	
}