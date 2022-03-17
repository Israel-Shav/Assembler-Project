# Commands and flags
CC = gcc -g 
CFLAGS = -Wall -ansi -pedantic 
LFLAGS = -I. -lm 

# Files names
HDRS = globals.h errors.h
OBJS = objects/assembler.o  objects/pre_assembler.o objects/first_phase.o objects/second_phase.o objects/output_producer.o objects/tables.o objects/storage.o objects/utils.o 

# Main execute file
assembler: $(OBJS) 
	$(CC) -o $@ $^ -lm

# Objects
objects/%.o: %.c %.h $(HDRS)
	@mkdir -p ./objects ./after_macro
	$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

# Clean section
clean: 
	find . -type f -name "*.o"  -exec rm -f {} \;
	find . -type f -name "*~" -exec rm -f {} \;
	find . -type f -name "*.bak" -exec rm -f {} \;
	find ./after_macro -type f -name "*.as" -exec rm -f {} \;