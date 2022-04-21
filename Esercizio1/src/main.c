#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../modules/sort.h"

struct Record{
  int id;
  char *field1;
  int field2;
  double field3;
};

//It takes as input two pointers to struct record.
//It returns 1 if the integer field of the first record is less than 
//the integer field of the second one (0 otherwise)
static int precedes_record_id(void* r1_p,void* r2_p){
  if(r1_p == NULL){
    fprintf(stderr,"precedes_record_id: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(r2_p == NULL){
    fprintf(stderr,"precedes_record_id: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  struct Record *rec1_p = (struct Record*)r1_p;
  struct Record *rec2_p = (struct Record*)r2_p;
  if(rec1_p->id < rec2_p->id){
    return 1;
  }
  return 0;
}


///It takes as input two pointers to struct record.
//It returns 1 iff the string field of the first record is less than 
//the string field of the second one (0 otherwise)

static int precedes_record_field1(void* r1_p,void* r2_p){
  if(r1_p == NULL){
    fprintf(stderr,"precedes_record_field1: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(r2_p == NULL){
    fprintf(stderr,"precedes_record_field1: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  struct Record *rec1_p = (struct Record*)r1_p;
  struct Record *rec2_p = (struct Record*)r2_p;
  if(strcmp(rec1_p->field1,rec2_p->field1)<0){
    return 1;
  }
  return 0;
}

static int precedes_record_field2(void* r1_p,void* r2_p){
  if(r1_p == NULL){
    fprintf(stderr,"precedes_record_field2: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(r2_p == NULL){
    fprintf(stderr,"precedes_record_field2: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  struct Record *rec1_p = (struct Record*)r1_p;
  struct Record *rec2_p = (struct Record*)r2_p;
  if(rec1_p->field2 < rec2_p->field2){
    return 1;
  }
  return 0;
}

static int precedes_record_field3(void* r1_p,void* r2_p){
  if(r1_p == NULL){
    fprintf(stderr,"precedes_record_field3: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(r2_p == NULL){
    fprintf(stderr,"precedes_record_field3: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  struct Record *rec1_p = (struct Record*)r1_p;
  struct Record *rec2_p = (struct Record*)r2_p;
  if(rec1_p->field3 < rec2_p->field3){
    return 1;
  }
  return 0;
}



static  void free_array(Sort* array) {
  unsigned long  el_num =  sort_size(array);
  for(unsigned long i=0;i<el_num;i++){
    struct Record *array_element = (struct Record *)sort_get(array, i);
    free(array_element->field1);
    free(array_element);
  }
  sort_free_memory(array);
}

static  void print_array(Sort* array){
  unsigned long el_num =  sort_size(array);
  struct Record *array_element;
  FILE *fp = fopen("output.csv", "w");
  //printf("\nQUICKSORT ARRAY OF RECORDS\n");
  
  for(unsigned long i=0;i<el_num;i++){
    array_element = (struct Record *)sort_get(array, i);
    fprintf(fp, "%d,%s,%d,%f\n", array_element->id, array_element->field1, array_element->field2, array_element->field3); 
  }
}

static void load_array(const char* file_name, Sort* array){
  char *read_line_p;
  char buffer[1024];
  int buf_size = 1024;
  FILE *fp;
  printf("\nLoading data from file...\n");
  fp = fopen(file_name,"r");
  if(fp == NULL){
    fprintf(stderr,"main: unable to open the file");
    exit(EXIT_FAILURE);
  }
  //int i = 0; 
  while(fgets(buffer,buf_size,fp) != NULL /*&& i != 1000000*/){  
    read_line_p = malloc((strlen(buffer)+1)*sizeof(char));
    if(read_line_p == NULL){
      fprintf(stderr,"main: unable to allocate memory for the read line");
      exit(EXIT_FAILURE);
    }   
    //i++;
    strcpy(read_line_p,buffer);   
    char *id_in_read_line_p = strtok(read_line_p,",");
    char *field1_in_read_line_p = strtok(NULL,",");
    char *field2_in_read_line_p = strtok(NULL,",");  
    char *field3_in_read_line_p = strtok(NULL,",");  
    int id = atoi(id_in_read_line_p);
    char *field1 = malloc((strlen(field1_in_read_line_p)+1)*sizeof(char));
    if(field1 == NULL){
      fprintf(stderr,"main: unable to allocate memory for the field1 of the read record");
      exit(EXIT_FAILURE);
    }  
    strcpy(field1,field1_in_read_line_p);
    int field2 = atoi(field2_in_read_line_p);
    double field3 = atof(field3_in_read_line_p); 
    struct Record *record_p = malloc(sizeof(struct Record));
    if(record_p == NULL){
      fprintf(stderr,"main: unable to allocate memory for the read record");
      exit(EXIT_FAILURE);
    }   
    record_p->id = id;
    record_p->field1 = field1;
    record_p->field2 = field2;
    record_p->field3 = field3;
    sort_add(array, (void*)record_p);
    free(read_line_p);
  }
  fclose(fp);
  printf("\nData loaded\n");
}

static  void test_with_comparison_function(const char* file_name, int (*compare)(void*, void*)) {
  Sort* array = sort_create(compare);
  load_array(file_name, array);
  clock_t time = clock();
  //quick_sort(array, 0, sort_size(array)-1);
  insertion_sort(array, sort_size(array)-1);
  printf("It took %f seconds to order the array\n", ((float)(clock() - time)/CLOCKS_PER_SEC));
  print_array(array);
  free_array(array);
}

//It should be invoked with one parameter specifying the filepath of the data file
int main(int argc, char const *argv[]) {
  if(argc < 2) {
    printf("Usage: sort_main <file_name>\n");  /* ? */
    exit(EXIT_FAILURE);
  }
  //test_with_comparison_function(argv[1], precedes_record_id);
  test_with_comparison_function(argv[1], precedes_record_field1);   
  //test_with_comparison_function(argv[1], precedes_record_field2);   
  //test_with_comparison_function(argv[1], precedes_record_field3);   
  return (EXIT_SUCCESS);
}

