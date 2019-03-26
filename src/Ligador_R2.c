#include "Machine_M2.h"
#include <string.h>

int search_address(char map, table* search, int table_size, int table_nmbr){
  int i = 0;
  int k = 1;
  if (table_nmbr == 0){
    for(i=0; i<table_size; i++){
      if (map == search[i].label){
        return search[i].address;
      }
    }
  }
  else if (table_nmbr == 1){
    while (search[i].label != '#') {
      if (map == search[i].label){
        return search[i].address;
      }
      i++;
    }
  }
  else{
    for(i=0; i<table_size;i++){
      if (search[i].label == '#'){
        k++;
        i++;
        if (k == table_nmbr){
          while (search[i].label != '#') {
            if (map == search[i].label){
              return search[i].address;
            }
            i++;
          }
        }
        else{
          i--;
        }
      }
    }
  }
  printf("Linker returned 1 failure\nCouldn't find declaration of function `%c´\n", map);
  exit(1); //ENDEREÇO INEXISTENTE
}

void write_final_file(char* final_file_name[], int file_numb, table* adjusted_table, int table_size, int* const_realoc){
  int current_table = 1;
  int aux = 0;
  int new_add = 0;
  int location_counter = 0;
  FILE* read_intermed = fopen("temp.r2", "r");
  FILE* final_file = fopen(final_file_name[file_numb-2], "w");
  char read_aux [32];
  while (fscanf(read_intermed, "%s\n", read_aux) > 0) {
    if (read_aux[0] == '#'){
      current_table++;
    }
    else if (read_aux[0] == '!'){
      new_add = search_address(read_aux[1], adjusted_table, table_size, 0);
      fprintf(final_file, "18\n%d\n", new_add - (location_counter+2));
    }
    else if (read_aux[0] == '*'){
      char destroy [2] = "*";
      char* pch = strtok(read_aux, destroy);
      aux = atoi(pch);
      fprintf(final_file, "%d\n", aux + const_realoc[current_table-1]);
    }
    else{
      fprintf(final_file, "%s\n", read_aux);
    }
    location_counter++;
  }
  fclose(read_intermed);
  fclose(final_file);
  return;
}

void adjust_table(table* to_adjust, int* adjust_parameter, int param_size, int table_size){
  int i = 0;
  int j = 0;
  for (i=0; i<table_size; i++){
    if (to_adjust[i].label == '#'){
      j++;
    }
    else{
      to_adjust[i].address += (adjust_parameter[j]);
    }
  }
  return;
}

void write_intermed_file(char* intrmed_file_name[], int respective_file, int* realoc_const){
  int transform = 0;
  int arguments = 0;
  int aux = 0;
  int instr;
  char label;
  char call_abs_add [32];
  char abs_adrresses[MAX_MEM][32];
  int count = 0;
  int i = 0;
  int j = 0;
  int v = 0;
  FILE* lnkr_code = fopen(intrmed_file_name[1], "r");
  FILE* intrmed_code = fopen("temp.r2", "w");
  fscanf(lnkr_code, "%c %d\n", &label, &instr);
  while (label != '#'){
    fscanf(lnkr_code, "%c %d\n", &label, &instr);
  }
  while (fscanf(lnkr_code, "%s\n", call_abs_add) > 0) {
    if (call_abs_add[0] == '!'){
      aux+=2;
      fprintf(intrmed_code, "%s\n", call_abs_add);
    }
    else{
      aux++;
      fprintf(intrmed_code, "%s\n", call_abs_add);
    }
  }
  realoc_const[1] += aux;
  fprintf(intrmed_code, "#\n");
  fclose(lnkr_code);

  for(i=2; i<respective_file-2; i++){
    FILE* lnkr_code = fopen(intrmed_file_name[i], "r");
    fscanf(lnkr_code, "%c %d\n", &label, &instr);
    while (label != '#'){
      fscanf(lnkr_code, "%c %d\n", &label, &instr);
    }
    while (fscanf(lnkr_code, "%s\n", call_abs_add) > 0) {
      if (call_abs_add[0] == '!'){
        aux+=2;
        fprintf(intrmed_code, "%s\n", call_abs_add);
      }
      else{
        aux++;
        fprintf(intrmed_code, "%s\n", call_abs_add);
      }
    }
    realoc_const[i] = aux + realoc_const[i+1];
    fprintf(intrmed_code, "#\n");
    fclose(lnkr_code);
  }
  fclose(intrmed_code);
  return;
}

void fill_table(table* tb_to_fill, char* file_name, int* cntr){
  char label_table;
  int addr_table;
  int run = MAX_MEM;
  FILE* mch_cd = fopen(file_name, "r");
  fscanf(mch_cd, "%c %d\n", &label_table, &addr_table);
  if (label_table == '#'){
    return;
  }
  tb_to_fill[(*cntr)].label = label_table;
  tb_to_fill[(*cntr)].address = addr_table;
  (*cntr)++;
  while (run) {
    fscanf(mch_cd, "%c %d\n", &label_table, &addr_table);
    if (label_table == '#'){
      return;
    }
    tb_to_fill[(*cntr)].label = label_table;
    tb_to_fill[(*cntr)].address = addr_table;
    (*cntr)++;
    run--;
  }
  fclose(mch_cd);
}

void print_table(table* to_print, int* cntr){
  int i = 0;
  for (i=0; i<(*cntr); i++){
    printf("Label: %c Addr: %d\n",to_print[i].label, to_print[i].address);
  }
}

int main(int argc, char *argv[]) {
  int* const_realoc = (int*)malloc((argc-1)*sizeof(int));
  int z = 0;
  int charge = atoi(argv[argc-1]);
  for (z=0; z<argc-1; z++){
    const_realoc[z] = charge;
  }
  int count = 0;
  int i = 0;
  int v = 0;
  table* linker_trouble = (table*)malloc(MAX_MEM*sizeof(table));
  for (i=1; i<argc-2; i++){
    fill_table(linker_trouble, argv[i], &count);
    linker_trouble[count].label = '#';
    linker_trouble[count].address = 0;
    count++;
  }
  write_intermed_file(argv, argc, const_realoc);
  adjust_table(linker_trouble, const_realoc, argc, count);
  write_final_file(argv, argc, linker_trouble, count, const_realoc);
  remove("temp.r2");
  return 0;
}
