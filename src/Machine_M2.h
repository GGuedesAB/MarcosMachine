#ifndef MACHINE_M2_H
#define MACHINE_M2_H

#include <stdlib.h>
#include <stdio.h>
#ifndef MAX_MEM
#define MAX_MEM 256
#endif

int PC;
int AC;
int RC;
int RX;
int MEM[MAX_MEM];

typedef struct instr{
	char label;
	char* op;
	char* var;
	int value;
	int size;
}instruction;

typedef struct linker_table
{
	char label;
	int address;
}table;

char verify_label_existance (char label, instruction* seek);

char verify_call_existance (char* call, instruction* seek);

int overall_inst (int opcode, int movement); //Executes instructions

int read_LS2code (char* location); //Counts LS2 instructions for memory allocation

int search_address(char map, table* search, int table_size, int table_nmbr);

int create_M2 (char* opcode, int var_address, FILE* S2, int* count, char unk);

int map_labels (instruction* map_unit, char label); //Creates a map of labels to get the correct addresses

instruction* read_file(char* symbols, int* k, int* i); //Reads the S2 file and returns label, opcode and operand inside a struct

void write_final_file(char* final_file_name[], int file_numb, table* adjusted_table, int table_size, int* const_realoc);

void adjust_table(table* to_adjust, int* adjust_parameter, int param_size, int table_size);

void write_intermed_file(char* intrmed_file_name[], int respective_file, int* realoc_const);

void fill_table(table* tb_to_fill, char* file_name, int* cntr);

void print_table(table* to_print, int* cntr);

void dump_MEM(int size); //Prints all the values in the memory with their relative addresses

void load_program (char* name, int displacement); //Loads the program in machine language format (*.M2) in memory

#endif
