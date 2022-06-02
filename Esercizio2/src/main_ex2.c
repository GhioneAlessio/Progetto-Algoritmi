#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "../modules/skiplist.h"

typedef struct _Sentence Sentence;

struct _Sentence{
  char **word_list;
  int sentence_size;
  int word_count;
};

void free_sentence(Sentence *sentence){
  for(int i = 0; i < sentence->word_count; i++)
    free(sentence->word_list[i]);
  free(sentence->word_list);
  free(sentence);
}

/* 
 * It takes as input two pointers.
 * It returns 1 if the string of the first pointer is less than 
 * the string of the second one, 0 if equal, -1 otherwise.
 */
static int precedes_string(void* str1_p,void* str2_p){
  if (str1_p == NULL){
    fprintf(stderr, "precedes_string: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (str2_p == NULL){
    fprintf(stderr, "precedes_string: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  return strcmp(str1_p, str2_p);
}

/*
 * It reads the input file containing the dictionary inserting the words in a SkipList.
 */
void read_file(const char* file_name, SkipList *skip_list){
  FILE *fp = fopen(file_name, "r");
  if(fp == NULL){
    fprintf(stderr,"main: unable to open the dictionary\n");
    exit(EXIT_FAILURE);
  }
  char *read_line_p;
  char buffer[1024];
  int buf_size = 1024;
  printf("\nLoading dictionary...\n");
  while(fgets(buffer, buf_size, fp)!= NULL){
    read_line_p = malloc((strlen(buffer)+1)*sizeof(char));
    if(read_line_p == NULL){
      fprintf(stderr,"main: unable to allocate memory for the read line\n");
      exit(EXIT_FAILURE);
    }
    strcpy(read_line_p,buffer);
    read_line_p[strlen(read_line_p) -1] = '\0'; /* metto il fine stringa un carattere prima, tolgo \n */
    skiplist_insert(skip_list, (void *)read_line_p);
  }
  printf("Dictionary loaded\n");
  fclose(fp);
}

/*
 * It reads the input file containing the sentences 
 * inserting the words in the Sentence struct.
 */
Sentence *read_sentence(const char* file_name, Sentence *sentence){
  FILE *fp = fopen(file_name, "r");
  if(fp == NULL){
    fprintf(stderr,"main: unable to open the file to correct\n");
    exit(EXIT_FAILURE);
  }
  int word_i = 0;
  char word[1024];
  memset(word, 0, sizeof(word));
  printf("\nLoading and correcting sentence...\n");
  char ch = fgetc(fp);
  while(ch != EOF){                     
    if(isalpha (ch)){
      ch = tolower(ch);
      word[word_i] = ch;  
      word_i++;
    }
    else if(word_i > 0){
      word[word_i]= '\0';
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
  
/*
 * Using skiplist_search, it corrects the file and prints the words 
 * that are not in the dictionary.
 */
void correct_file(Sentence *sentence, SkipList *dictionary){
  for(int i = 0; i < sentence->word_count; i++){
    if(skiplist_search(dictionary, sentence->word_list[i]) == NULL){
      printf("%s\n", sentence->word_list[i]);
    }
  }
}

/*
 * It takes the dictionary file and the file to be corrected as input.
 */
int main(int argc, char const *argv[]) {
  if(argc < 3) {
    printf("Too few arguments\n");  
    exit(EXIT_FAILURE);
  }
  clock_t time = clock();
  srand(time);
  SkipList *dictionary_list = skiplist_create(precedes_string);
  read_file(argv[1], dictionary_list);
  Sentence *sentence = (Sentence *)malloc(sizeof(Sentence));
  if(sentence == NULL){
    printf("Main - sentence : Unable to allocate memory\n");
    exit(EXIT_FAILURE);
  }
  sentence->sentence_size = 1;
  sentence->word_count = 0;
  sentence->word_list = malloc(sizeof(char *) * sentence->sentence_size);
  sentence = read_sentence(argv[2], sentence);
  correct_file(sentence, dictionary_list);
  printf("It took %f seconds to upload the dictionary and correct the sentence\n", ((float)(clock() - time)/CLOCKS_PER_SEC));
  free_sentence(sentence);
  skiplist_free(dictionary_list, free);
  return 0;
}
