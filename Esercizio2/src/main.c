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
  return strcmp(r1_p, r2_p);
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
	int count = 0;
  printf("\nLoading data from file...\n");
  while(fgets(buffer, buf_size, fp)!= NULL && count < 50){
    read_line_p = malloc((strlen(buffer)+1)*sizeof(char));
    if(read_line_p == NULL){
      fprintf(stderr,"main: unable to allocate memory for the read line\n");
      exit(EXIT_FAILURE);
    }
    strcpy(read_line_p,buffer);
	read_line_p[strlen(read_line_p) -1] = '\0'; // metto il fine stringa un carattere prima, tolgo \n 
    SkipList_insert(skip_list, (void *)read_line_p);
	count++;
  }
  fclose(fp);
}

void print_list(SkipList *skip_list){
	printf("print\n");
  Node *current_node = skip_list->head;
 int cont = 0;
  while (current_node != NULL) {
      printf("%d - %s\n", cont,(char *) (current_node->item));
      current_node = current_node->next[0];
	  cont++;
  }
  printf("fffff\n");
}

int main(int argc, char const *argv[]) {
  if(argc < 2) {
    printf("Too few arguments\n");  
    exit(EXIT_FAILURE);
  }
  SkipList *skip_list = SkipList_create(precedes_string);
  read_file(argv[1], skip_list);
  print_list(skip_list);
  printf("dopo\n");
  
  
  return 0;
}
