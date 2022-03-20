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
 * @param filename 
 */
void build_output_files(char *filename) 
{
	print_label_table();
	
	print_storage_table();
}


	