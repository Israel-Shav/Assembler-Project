/*
    Program: Assembler
    Author: Israel Shalmiev and Roei Levi
    
    Assembler for 15-instruction asssembly language, for an imaginary 16-bit CPU and 20 bits of memory size.
*/
#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "assembler.h"
#include "pre_assembler.h"
#include "first_phase.h"
#include "second_phase.h"
#include "storage.h"
#include "tables.h"
#include "output_producer.h"
#include "errors.h"
#include "utils.h"

/**
 * Entry point - 20bit assembler. Assembly language specified in booklet.
 */
int main(int argc, char *argv[]) 
{
	/* To break line if needed */
	bool succeeded;
    int i;
	/* Process each file from args */
	for (i = 1, succeeded = True; i < argc; i++) 
    {
		/* New line if last file proccess failed */
		/* if (!succeeded) 
            puts(""); */
		/* Process each file */
		succeeded = process_file(argv[i]);
		printf(succeeded ? "Process completed successfully on compiling %s.\n" : "Process FAILED on compiling %s!\n", getFileName(argv[i]));
	}
	return NO_ERRORS_EC;
}

static bool process_file(char *filename) 
{
    /* Status of process if succeed */
	bool is_process_stable;
	char *full_filename;

    /* Macro phase: save a pointer to macrolated file */
    is_process_stable = ((full_filename = macro_phase_process(filename)) != NULL);


    /* Continue initializing phase and start first phase: update status if the process is succeed */
    is_process_stable = first_phase_process(full_filename);

	if (is_process_stable)
        is_process_stable = pre_second_phase_data_update();
	

    /* Second phase: update status if the process is succeed */
	if (is_process_stable)
        is_process_stable = second_phase_process(full_filename);

    /* Output phase: creates output files if process is stable */
    if (is_process_stable)
        build_output_files(filename);

    /* Garbage collector: */
	/* Free all tables */
	tables_dispose();
	/* Free storage code and data buffers contents */
	storage_dispose();
    /* Full file name */
	free(full_filename);

	/* Returns if the process is succeed */
	return is_process_stable;
}