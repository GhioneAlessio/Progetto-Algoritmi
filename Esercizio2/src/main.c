#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "../modules/skiplist.h"

typedef struct _Sentence Sentence;

struct _Sentence
{
  char **word_list;
  int sentence_size;
  int word_count;
};

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

Sentence *read_sentence(const char* file_name, Sentence *sentence){
  FILE *fp = fopen(file_name, "r");
  if(fp == NULL){
    fprintf(stderr,"main: unable to open the file2\n");
    exit(EXIT_FAILURE);
  }
  int word_i = 0;
  char word[1024];
  memset(word, 0, sizeof(word));
  printf("\nLoading data from file2...\n");
  char ch = fgetc(fp);
  while(ch != EOF){
                            
    if(isalpha (ch)){
      ch = tolower(ch);
      word[word_i] = ch;  
      word_i++;
    }
    
    else if(word_i > 0){
      char *tmp_word = malloc((strlen(word)+1)*sizeof(char));
      strcpy(tmp_word, word);  
      if(sentence->word_count  >= sentence->sentence_size){
        sentence->word_list = realloc(sentence->word_list, 2 * sentence->sentence_size * sizeof(word));
        sentence->sentence_size *= 2;
      }
      sentence->word_list[sentence->word_count] = tmp_word;
      sentence->word_count++;
      word_i = 0;
      memset(word, 0, sizeof(word));
    }
    ch = fgetc(fp);
  }
  fclose(fp);
  return sentence;
  }

void correct_file(Sentence *sentence, SkipList *dictionary){
  for(int i = 0; i < sentence->word_count; i++){
    if(SkipList_search(dictionary, sentence->word_list[i]) == NULL){
      printf("%s\n", sentence->word_list[i]);
    }
  }
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
  if(argc < 3) {
    printf("Too few arguments\n");  
    exit(EXIT_FAILURE);
  }
  srand(time(NULL));
  SkipList *dictionary_list = SkipList_create(precedes_string);
  read_file(argv[1], dictionary_list);
  
  Sentence *sentence = (Sentence *)malloc(sizeof(Sentence));
  if(sentence == NULL){
    printf("Main - sentence : Unable to allocate memory\n");
    exit(EXIT_FAILURE);
  }
  sentence->sentence_size = 2;
  sentence->word_count = 0;
  sentence->word_list = malloc(sizeof(char *) * sentence->sentence_size);
  sentence = read_sentence(argv[2], sentence);
  correct_file(sentence, dictionary_list);
  return 0;
}
