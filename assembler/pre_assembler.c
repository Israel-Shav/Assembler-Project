#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "globals.h"
#include "pre_assembler.h"
#include "errors.h"
#include "tables.h"
#include "utils.h"

/**
 * @brief Creates copy of source file, replace any macro statement with its content and removes unnecessary macros definitions (removes comments in macro defenitions too)
 * @param filename Extensionless file name
 * @return After macro phase edit source file
 */
char *macro_phase_process(char *filename)
{
	/* Declarations */
	FILE *file_des, *macro_file_des;
	char *full_filename, *macro_full_filename, temp_line[MAX_LINE_LENGTH + 2], temp_c, *macro_name;
	bool is_process_stable, is_macro_block;
	int line_number;


	/* Initializing macro table */
	if(!init_macro_table())
		return NULL;

    /* Duplicate as file */
    full_filename = strallocat(filename, SOURCE_FILE_EXTENSION);
	macro_full_filename = strallocat(AFTER_MACRO_DIR, getFileName(full_filename));

    /* Open file, skip on failure, current assembly file descriptor to process */
	file_des = fopen(full_filename, READ_PERMISSIONS);
	if (file_des == NULL) 
	{
		/* if file couldn't be opened, write to stderr. */
		printf(READING_PERMISSIONS_ERROR(full_filename));
		free(full_filename);
		free(macro_full_filename);
		return NULL;
	}

	/* Open file, skip on failure, current assembly file descriptor to process */
	macro_file_des = fopen(macro_full_filename, WRITE_PERMISSIONS);
	if (macro_file_des == NULL) 
	{
		/* if file couldn't be opened, write to stderr. */
		printf(READING_PERMISSIONS_ERROR(macro_full_filename));
		free(full_filename);
		free(macro_full_filename);
		fclose(file_des);
		return NULL;
	}

	/* Read line - stop if read failed (when NULL returned) - usually when EOF. increase line counter for error printing. */
	for (line_number = 1, is_process_stable = True, is_macro_block = False, macro_name = NULL; 
		fgets(temp_line, MAX_LINE_LENGTH + 2, file_des) != NULL; line_number++) 
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
			if (!macro_line_process(temp_line, &is_macro_block, macro_name, macro_file_des) && is_process_stable)
			{

				is_process_stable = False;
			}
		}
	}
	free(full_filename);
	fclose(macro_file_des);
	fclose(file_des);
	if (is_process_stable)
		return macro_full_filename;
	return NULL;
}

/**
 * @brief Processes a single line in the macro phase (removes comments in macro defenitions too)
 * @param line The line text
 * @param is_macro_block Is reading macro block
 * @param macro_name Macro name
 * @return Whether succeeded.
 */
static bool macro_line_process(char *line, bool *is_macro_block, char *macro_name, FILE* new_file) 
{
	char *token, *copy_line = (char *)malloc_with_check(strlen(line) + 1), *macro_data;
	strcpy(copy_line, line);

	/* Get the first token */
   token = strtok(line, TOKENS_DELIMITERS);
   
   /* walk through other tokens */
   if( token != NULL ) 
   {
      	if(*is_macro_block)
		{
			if(strcmp(token, MACRO_END_STATEMENT) == 0)
			{
				*is_macro_block = False;
				free(macro_name);
			}
			else if(strcmp(token, "") != 0 && token[0] != COMMENT)
				insert_macro(macro_name, copy_line);
		}
		else 
		{
			if(strcmp(token, MACRO_START_STATEMENT) == 0)
			{
				*is_macro_block = True;
				macro_name = (char *)malloc_with_check(strlen(token) + 1);
				strcpy(macro_name, token);
			}
			else if((macro_data = get_macro_code(macro_name)) != NULL)
				fprintf(new_file, macro_data);
			else
				fprintf(new_file, copy_line);
		}
   }
   free(copy_line);
   return True;
}