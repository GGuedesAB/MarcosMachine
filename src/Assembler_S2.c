#include "Machine_M2.h"
#include <unistd.h>
#include <string.h>
#define MAX_READ 50000

char verify_label_existance (char label, instruction* seek){
	int i = 0;
	int j = 0;
	for (i=0; i<seek[0].size; i++){
		if (label != *(seek[i].var)){
			if (j == seek[0].size - 1){
				return label;
			}
			j++;
		}
	}
	return 0;
}

char verify_call_existance (char* call, instruction* seek){
	int i = 0;
	int j = 0;
	for (i=0; i<seek[0].size; i++){
		if (*(call) != seek[i].label){
			if (j == seek[0].size - 1){
				return *(call);
			}
			j++;
		}
	}
	return 0;
}

int read_LS2code (char* location){
	FILE* instructions = fopen(location, "r");
	if (NULL == instructions){
		printf("Instruction file not found.\n");
		exit(1);
	}
	char counter[10];
	int i = 0;
	while (fgets(counter, 10, instructions) > 0){
		i++;
	}
	fclose (instructions);
	return i;
}

int create_M2 (char* opcode, int var_address, FILE* S2, int* count, char unk){
	if (strcmp("CAL_UNK", opcode) == 0){
		(*count)+=2;
		fprintf(S2, "!%c\n", unk);
		return 1;
	}
	if (strcmp("LAD", opcode) == 0){ //LAD
		(*count)+=2;
		fprintf(S2, "1\n%d\n", var_address - *count);
		return 1;
	}
	else if (strcmp("SAD", opcode) == 0){ //SAD
		(*count)+=2;
		fprintf(S2, "2\n%d\n", var_address - *count);
		return 1;
	}
	else if (strcmp("ADD", opcode) == 0){ //ADD
		(*count)+=2;
		fprintf(S2, "3\n%d\n", var_address - *count);
		return 1;
	}
	else if (strcmp("SUB", opcode) == 0){ //SUB
		(*count)+=2;
		fprintf(S2, "4\n%d\n", var_address - *count);
		return 1;
	}
	else if (strcmp("INP", opcode) == 0){ //INP
		(*count)+=2;
		fprintf(S2, "5\n%d\n", var_address - *count);
		return 1;
	}
	else if (strcmp("OUT", opcode) == 0){ //OUT
		(*count)+=2;
		fprintf(S2, "6\n%d\n", var_address - *count);
		return 1;
	}
	else if (strcmp("JMP", opcode) == 0){ //JMP
		(*count)+=2;
		fprintf(S2, "7\n%d\n", var_address - *count);
		return 1;
	}
	else if (strcmp("JGZ", opcode) == 0){ //JGZ
		(*count)+=2;
		fprintf(S2, "8\n%d\n", var_address - *count);
		return 1;
	}
	else if (strcmp("JLZ", opcode) == 0){ //JLZ
		(*count)+=2;
		fprintf(S2, "9\n%d\n", var_address - *count);
		return 1;
	}
	else if (strcmp("JZE", opcode) == 0){ //JZE
		(*count)+=2;
		fprintf(S2, "10\n%d\n", var_address - *count);
		return 1;
	}
	else if (strcmp("HLT", opcode) == 0){ //HLT
		(*count)+=2;
		fprintf(S2, "11\n00\n");
		return 0;
	}
	else if (strcmp("LXD", opcode) == 0){ //LXD
		(*count)+=2;
		fprintf(S2, "12\n%d\n", var_address - *count);
		return 1;
	}
	else if (strcmp("SXD", opcode) == 0){ //SXD
		(*count)+=2;
		fprintf(S2, "13\n%d\n", var_address - *count);
		return 1;
	}
	else if (strcmp("LAX", opcode) == 0){ //LAX
		(*count)+=2;
		fprintf(S2, "14\n%d\n", var_address - *count);
		return 1;
	}
	else if (strcmp("SAX", opcode) == 0){ //SAX
		(*count)+=2;
		fprintf(S2, "15\n%d\n", var_address - *count);
		return 1;
	}
	else if (strcmp("LCD", opcode) == 0){ //LCD
		(*count)+=2;
		fprintf(S2, "16\n%d\n", var_address - *count);
		return 1;
	}
	else if (strcmp("JCC", opcode) == 0){ //JCC
		(*count)+=2;
		fprintf(S2, "17\n%d\n", var_address - *count);
		return 1;
	}
	else if (strcmp("CAL", opcode) == 0){ //CAL
		(*count)+=2;
		fprintf(S2, "18\n%d\n", var_address - *count);
		return 1;
	}
	else if (strcmp("RET", opcode) == 0){ //RET
		(*count)+=2;
		fprintf(S2, "19\n00\n");
		return 1;
	}
	else if (strcmp("LAI", opcode) == 0){ //LAI
		(*count)+=2;
		fprintf(S2, "20\n00\n");
		return 1;
	}
	else if (strcmp("SAI", opcode) == 0){ //SAI
		(*count)+=2;
		fprintf(S2, "21\n00\n");
		return 1;
	}
	else if (strcmp("DOB", opcode) == 0){ //DOB
		(*count)+=2;
		fprintf(S2, "22\n00\n");
		return 1;
	}
	else if (strcmp("MET", opcode) == 0){
		(*count)+=2;
		fprintf(S2, "23\n00\n");
		return 1;
	}
	else if (strcmp("JPA", opcode) == 0){
		(*count)+=2;
		fprintf(S2, "24\n%d\n", var_address - *count);
		return 1;
	}
	//O que eu faço com DC?
	else if (strcmp("DC", opcode) == 0){ //DC
		(*count)++;
		fprintf(S2, "%d\n", var_address);
		return 1;
	}
	else if (strcmp("DS", opcode) == 0){ //DS
		(*count)++;
		int i = 0;
		for (i=0; i<var_address; i++){
			fprintf(S2, "0\n");
			if (i == var_address-1){
				return 1;
			}
			(*count)++;
		}
		return 1;
	}
	else if (strcmp("DA", opcode) == 0){ //DA
		(*count)++;
		fprintf(S2, "*%d\n", var_address);
		RX = 0;
		return 1;
	}
}

instruction* read_file(char* symbols, int* k, int* i){
	FILE* assembly = fopen(symbols, "r");
	instruction* instr = (instruction*)malloc((*i)*sizeof(instruction));
	instr[0].size = *i;
	int j = *k;
	if (NULL == instr){
		printf("Allocation ERROR\n");
		exit(1);
	}
  char buffer[10];
  instr[j].label = fgetc(assembly);
  while ((fgets(buffer, 10, assembly)) > 0) {
  	char* pch = strtok(buffer, "\n");
  	char* opcode = strtok(pch, " ");
  	instr[j].op = (char*)malloc(4*sizeof(char));
		instr[j].var = (char*)malloc(sizeof(char));
  	while(NULL != opcode){
  		strcpy(instr[j].op, opcode);
  		if (strcmp(instr[j].op, "DS") == 0 || strcmp(instr[j].op, "DC") == 0){
  			opcode = strtok(NULL, " ");
  			instr[j].value = atoi(opcode);
  		}
  		else{
  			opcode = strtok(NULL, " ");
  			if (opcode == NULL){
  				opcode = " ";
  			}
			strcpy(instr[j].var, opcode);
  		}
  		opcode = strtok(NULL, " ");
  	}
  	if (j<(*i)-1){
		instr[j+1].label = fgetc(assembly);
  	}
  	j++;
  }
  fclose(assembly);
	*k = j;
  return instr;
}

int map_labels (instruction* map_unit, char label){
	int i = 0;
	int j = 0;
	int found = 0;
	while(strcmp(map_unit[i].op, "END") != 0){
		if (map_unit[i].label == label){
			return j;
		}
		else if (strcmp(map_unit[i].op, "DS") == 0){
			j = j + map_unit[i].value;
		}
		else if (strcmp(map_unit[i].op, "DC") == 0){
			j++;
			found = 1;
			if (map_unit[i].label == label){
				return j;
			}
		}
		else if (strcmp(map_unit[i].op, "DA") == 0){
			j++;
			if (map_unit[i].label == label){
				found = 1;
				return j;
			}
		}
		else{
			j+=2;
		}
		i++;
	}
}

int main(int argc, char *argv[]) {
	int aloc_size = read_LS2code(argv[1]);
	int aux = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int counter = 0;
	int mapped = 0;
	char check_call = 0;
	char check_label = 0;
	char check_address = 0;
	char unknwn_call [MAX_MEM];
	char label_loc [MAX_MEM];
	int addr [MAX_MEM];
	aux = read_LS2code(argv[1]);
	instruction* comands = read_file(argv[1], &j, &aux);
	FILE* machine_code = fopen(argv[2], "w");
	char* unfnd = (char*)malloc(sizeof(char));
	while (strcmp(comands[i].op, "END") != 0){
		check_label = verify_label_existance(comands[i].label, comands);
		if (check_label){
			label_loc[k] = check_label;
			k++;
		}
		if (strcmp(comands[i].op, "CAL") == 0){
			check_call = verify_call_existance(comands[i].var, comands);
			if (check_call){
				create_M2("CAL_UNK", 0, machine_code, &counter, check_call);
			}
			if (!check_call && !check_label){
				mapped = map_labels(comands, *(comands[i].var));
				create_M2(comands[i].op, mapped, machine_code, &counter, 0);
			}
		}

		else{
			mapped = map_labels(comands, *(comands[i].var));
			if (strcmp(comands[i].op, "DS") == 0 || strcmp(comands[i].op, "DC") == 0){
				label_loc[k] = comands[i].label;
				k++;
				create_M2(comands[i].op, comands[i].value, machine_code, &counter, 0);
			}
			else{
				create_M2(comands[i].op, mapped, machine_code, &counter, 0);
			}
		}
		i++;
	}
	char* TEXT = (char*)malloc(MAX_READ*sizeof(char));
	if (TEXT == NULL){
		fprintf(stderr, "**Not enough memory for program**\n");
	}
	fclose(machine_code);
	machine_code = fopen(argv[2], "r");
	fread(TEXT, 1, MAX_READ, machine_code);
	fclose(machine_code);
	machine_code = fopen(argv[2], "w");
	for (i=0; i<k; i++){
		fprintf(machine_code, "%c %d\n", label_loc[i], map_labels(comands, label_loc[i]));
	}
	fprintf(machine_code, "# 0\n");
	fputs(TEXT, machine_code);
	fclose(machine_code);
	for(i=0; i<aloc_size; i++){
		free(comands[i].op);
		free(comands[i].var);
	}
	free(comands);
	free(TEXT);
	free(unfnd);
	return 0;
}
