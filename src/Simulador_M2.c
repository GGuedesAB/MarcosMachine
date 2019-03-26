#include "Machine_M2.h"
#include <string.h>

int overall_inst (int opcode, int movement){
	if (0 == opcode){
		fprintf(stderr, "*Unknown instruction on memory. Dumping and exiting.\n");
		dump_MEM(MAX_MEM);
		exit(1);
	}
	else if (1 == opcode){ //LAD
		PC += 2;
		AC = MEM[PC+movement];
		return 1;
	}
	else if (2 == opcode){ //SAD
		PC += 2;
		MEM[PC+movement] = AC;
		return 1;
	}
	else if (3 == opcode){ //ADD
		PC += 2;
		AC += MEM[PC+movement];
		return 1;
	}
	else if (4 == opcode){ //SUB
		PC += 2;
		AC -= MEM[PC+movement];
		return 1;
	}
	else if (5 == opcode){ //INP
		PC += 2;
		scanf("%d", &MEM[PC+movement]);
		return 1;
	}
	else if (6 == opcode){ //OUT
		PC += 2;
		printf("%d\n", MEM[PC+movement]);
		return 1;
	}
	else if (7 == opcode){ //JMP
		PC = PC+movement+2;
		return 1;
	}
	else if (8 == opcode){ //JGZ
		if (AC > 0){
			PC += movement+2;
		}
		else PC += 2;
		return 1;
	}
	else if (9 == opcode){ //JLZ
		if (AC < 0){
			PC += movement+2;
		}
		else PC += 2;
		return 1;
	}
	else if (10 == opcode){ //JZE
		if (AC == 0){
			PC += movement+2;
		}
		else PC += 2;
		return 1;
	}
	else if (11 == opcode){ //HLT
		return 0;
	}
	else if (12 == opcode){ //LXD
		PC += 2;
		RX = MEM[PC+movement];
		return 1;
	}
	else if (13 == opcode){ //SXD
		PC += 2;
		MEM[PC+movement] = RX;
		return 1;
	}
	else if (14 == opcode){ //LAX
		PC += 2;
		AC = RX;
		RX = RX+1;
		return 1;
	}
	else if (15 == opcode){ //SAX
		PC+= 2;
		RX = AC;
		RX = RX+1;
		return 1;
	}
	else if (16 == opcode){ //LCD
		PC += 2;
		RC = MEM[PC+movement];
		return 1;
	}
	else if (17 == opcode){ //JCC
		RC = RC-1;
		if (RC > 0){
			PC += movement+2;
		}
		else{
			PC += 2;
		}
		return 1;
	}
	else if (18 == opcode){ //CAL
		RX = PC+2;
		PC += movement+2;
		return 1;
	}
	else if (19 == opcode){ //RET
		PC = RX;
		return 1;
	}
	else if (20 == opcode){ //LAI
		PC += 2;
		AC = MEM[MEM[RX]];
		RX++;
		return 1;
	}
	else if (21 == opcode){ //SAI
		PC += 2;
		MEM[MEM[RX]] = AC;
		RX++;
		return 1;
	}
	else if (22 == opcode){ //DOB
		PC +=2;
		AC += AC;
		return 1;
	}
	else if (23 == opcode){ //MET
		PC+= 2;
		AC = AC/2;
		return 1;
	}
	else if (24 == opcode){ //JPA
		if ((AC%2) == 0){
			PC += movement + 2;
		}
		else PC+=2;
	}
}

void dump_MEM(int size){
	FILE* dump = fopen("MEM_DUMP", "w");
	int i = 0;
	fprintf(dump, "**MEM dump**\n");
	for (i=0; i<size; i++){
		fprintf(dump, "Address:%d - Value:%d\n", i, MEM[i]);
	}
}

void load_program (char* name, int displacement){
	int current_PC = 0;
	int i = 0;
	int m2 = 0;
	FILE* M2 = fopen(name, "r");
	while (fscanf(M2, "%d\n", &m2) > 0) {
		MEM[i+displacement] = m2;
		i++;
	}
	fclose(M2);
	return;
}

int main (int agrc, char* argv[]){
	PC = 0;
	AC = 0;
	RC = 0;
	RX = 0;
	int on = 1;
	int displacement = atoi(argv[2]);
	PC = displacement;
	load_program(argv[1], displacement);
	while (on){
		on = overall_inst(MEM[PC], MEM[PC+1]);
		if (on == 2){
			fprintf(stderr, "*Unknown instruction on memory. Dumping and exiting.\n");
		}
	}
	dump_MEM(MAX_MEM);
	return 0;
}
