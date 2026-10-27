# Makefile for Homework 0.5 | CSCI 2410 | GWU
# 
# this Makefile supports the following commands:
## make: to build the sort executable
## make tests: to run tests after building the sort executable
## make clean: to remove object files and executable

CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = sort.o helper_functions.o sorting_function.o
TARGET = sort
TEMP = sols/
.PHONY: all clean
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
%.o: %.c sorting_function.h helper_functions.h
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(OBJ) $(TARGET) $(TEMP)
tests: $(TARGET)
	mkdir -p tests/test_outputs
	for file in tests/*.txt; do \
		echo "--------------------------------"; \
		echo "Test: $$file\n"; \
		output_name_file=tests/test_outputs/$$(basename $$file).name; \
		output_id_file=tests/test_outputs/$$(basename $$file).id; \
		./$(TARGET) name $$file $$output_name_file; \
		./$(TARGET) id $$file $$output_id_file; \
		echo "Output NAME base file: $$output_name_file\n"; \
		echo "Output ID base file: $$output_id_file\n"; \
		echo "--------------------------------"; \
	done

frame:
	gcc test_script.c sorting_function.c helper_functions.c -o test_script -I .