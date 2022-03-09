/**
 * @brief Allocates and builds the data inside the additional code word by the given operand,
 *        Only in the macro phase
 * @param code_img The current code image
 * @param ic The current instruction counter
 * @param operand The operand to check
 */
char *macro_phase_process(*filename)
{

    /* Concat extensionless filename with .as extension */
    full_filename = strallocat(filename, SOURCE_FILE_EXTENSION);

    /* Open file, skip on failure */
	file_des = fopen(full_filename, "r");
	if (file_des == NULL) {
		/* if file couldn't be opened, write to stderr. */
		printf(READING_PERMISSIONS_ERROR(full_filename));
		free(full_filename); /* The only allocated space is for the full file name */
		return NULL;
	}

	/* start first pass: */
	curr_line_info.file_name = full_filename;
	curr_line_info.content = temp_line; /* We use temp_line to read from the file, but it stays at same location. */
	/* Read line - stop if read failed (when NULL returned) - usually when EOF. increase line counter for error printing. */
	for (curr_line_info.line_number = 1;
	     fgets(temp_line, MAX_LINE_LENGTH + 2, file_des) != NULL; curr_line_info.line_number++) {
		/* if line too long, the buffer doesn't include the '\n' char OR the file isn't on end. */
		if (strchr(temp_line, '\n') == NULL && !feof(file_des)) {
			/* Print message and prevent further line processing, as well as second pass.  */
			printf_line_error(curr_line_info, "Line too long to process. Maximum line length should be %d.",
			                  MAX_LINE_LENGTH);
			process_status = FALSE;
			/* skip leftovers */
			do {
				temp_c = fgetc(file_des);
			} while (temp_c != '\n' && temp_c != EOF);
		} else {
			if (!line_process(curr_line_info, &ic, &dc, code_img, data_img, &symbol_table)) {
				if (process_status) {
					/*free_code_image(code_img, ic_before);*/
					icf = -1;
					process_status = FALSE;
				}
			}
		}
	}

	/* Save ICF & DCF (1.18) */
	icf = ic;
	dcf = dc;
}