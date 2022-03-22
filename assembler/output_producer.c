#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "storage.h"
#include "tables.h"
#include "output_producer.h"
#include "errors.h"
#include "utils.h"

/**
 * @brief 
 * 
 * @param new_filename 
 */
void build_output_files(char *filename) 
{
    /* Declarations */
	char *part_filename, *full_filename;

	print_label_table();
	
	print_storage_table();

    /* Object file */
    part_filename = strallocat(filename, OBJECTS_FILE_EXTENSION);
	full_filename = strallocat(OUTPUT_DIR, getFileName(part_filename));
	free(part_filename);
    create_object_file(full_filename);
    free(full_filename);

    /* Entry file */
    part_filename = strallocat(filename, ENTERIES_FILE_EXTENSION);
	full_filename = strallocat(OUTPUT_DIR, getFileName(part_filename));
	free(part_filename);
    create_entries_file(full_filename);
    free(full_filename);

    /* External file */
    part_filename = strallocat(filename, EXTERNALS_FILE_EXTENSION);
	full_filename = strallocat(OUTPUT_DIR, getFileName(part_filename));
	free(part_filename);
    create_externals_file(full_filename);
    free(full_filename);
}


	