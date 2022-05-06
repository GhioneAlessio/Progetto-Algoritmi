#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../modules/skiplist.h"

static int precedes_string(void* r1_p,void* r2_p){
  if (r1_p == NULL){
    fprintf(stderr, "precedes_record_field1: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL){
    fprintf(stderr, "precedes_record_field1: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (strcmp(r1_p, r2_p) < 0)
    return 1;
  else if(strcmp(r1_p, r2_p) == 0)
    return 0;
  else 
    return -1;
}

void read_file(const char* file_name, SkipList *skip_list){

  FILE *fp = fopen(file_name, "r");
  if(fp == NULL){
    fprintf(stderr,"main: unable to open the file\n");
    exit(EXIT_FAILURE);
  }

  char *read_line_p;
  char buffer[1024];
  int buf_size = 1024;

  printf("\nLoading data from file...\n");
  while(fgets(buffer, buf_size, fp)!= NULL ){
    read_line_p = malloc((strlen(buffer)+1)*sizeof(char));
    if(read_line_p == NULL){
      fprintf(stderr,"main: unable to allocate memory for the read line\n");
      exit(EXIT_FAILURE);
    }
    strcpy(read_line_p,buffer);
    SkipList_insert(skip_list, read_line_p);
  }
  fclose(fp);
}

int main(int argc, char const *argv[]) {
  if(argc < 2) {
    printf("Too few arguments\n");  
    exit(EXIT_FAILURE);
  }
  SkipList *skip_list = SkipList_create(precedes_string);
  read_file(argv[1], skip_list);
  print_list(skip_list);
  return 0;
}
