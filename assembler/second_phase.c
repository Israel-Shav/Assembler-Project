ic = IC_INIT_VALUE;

	/* Now let's add IC to each DC for each of the data symbols in table (step 1.19) */
	add_value_to_type(symbol_table, icf, DATA_SYMBOL);

	/* First pass done right. start second pass: */
	rewind(file_des); /* Start from beginning of file again */

	for (curr_line_info.line_number = 1; !feof(file_des); curr_line_info.line_number++) {
		int i = 0;
		fgets(temp_line, MAX_LINE_LENGTH, file_des); /* Get line */
		MOVE_TO_NOT_WHITE(temp_line, i)
		if (code_img[ic - IC_INIT_VALUE] != NULL || temp_line[i] == '.')
			process_status &= process_line_spass(curr_line_info, &ic, code_img, &symbol_table);
	}

		/* Write files if second pass succeeded */
		if (process_status) {
			/* Everything was done. Write to *filename.ob/.ext/.ent */
			process_status = write_output_files(code_img, data_img, icf, dcf, filename, symbol_table);
		}