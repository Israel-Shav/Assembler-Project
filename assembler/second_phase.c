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
 * @brief Static declartions: should be only in same file otherwise it will be copied
 * 
 */

/**
 * @brief Processes a single line in the second phase
 * @param line The line text
 * @param bool Indicates if process stable
 * @return Whether succeeded.
 */
static bool sp_line_process(char *line, bool *is_process_stable, char *filename, int line_number);


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
		printf(READING_PERMISSIONS_ERROR, full_filename);
		return False;
	}
	
	/* Read line - stop if read failed (when NULL returned) - usually when EOF. increase line counter for error printing. */
	for (line_number = 1, is_process_stable = pre_second_phase_data_update(); fgets(temp_line, MAX_LINE_LENGTH + 2, file_des) != NULL; line_number++) 
	{
		/* if line too long, the buffer doesn't include the NEW_LINE='\n' char and the file isn't on end. */
		if (strchr(temp_line, NEW_LINE) == NULL && !feof(file_des))
		{
			/* Print message and prevent further line processing, as well as second pass.  */
			fprintf(ERR_OUTPUT_FILE, TOO_LONG_INPUT_LINE, full_filename, line_number, MAX_LINE_LENGTH);
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
			if (!sp_line_process(temp_line, &is_process_stable, full_filename, line_number) && is_process_stable)
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
	char *token, *copy_line, *rest_of_str;
	bool is_labeled;
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
		/* Get second token */
		token = strtok(NULL, TOKENS_DELIMITERS);
		if( token == NULL ) 
		{
			printf(EMPTY_LABEL_LINE, filename, line_number, copy_line);
			free(copy_line);
			return False;
		}
	}


	if(strcmp(token, ".entry") == 0)
	{
		rest_of_str = strtok(NULL, NEW_LINE_DELIMITERS);
		if(rest_of_str == NULL)
		{
			printf(EMPTY_EXTERN_LINE, filename, line_number, copy_line);
			free(copy_line);
			return False;
		}
		SKIP_WHITE_CHARS_PNT(rest_of_str)
		if(*is_process_stable)
			*is_process_stable = add_entry_attribute(rest_of_str);
	}
	else if(is_action_exist(token))
	{
		rest_of_str = strtok(NULL, NEW_LINE_DELIMITERS);
		if(rest_of_str != NULL)
			SKIP_WHITE_CHARS_PNT(rest_of_str)
		if(*is_process_stable)
			*is_process_stable = second_encode_instruction(token, rest_of_str, filename, line_number);
	}
	free(copy_line);
	return True;
	
}