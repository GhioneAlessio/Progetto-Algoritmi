#include <stdio.h>
#include <stdlib.h>
#include "skiplist.h"

/*
 * It creates the SkipList and it initialises it.
 */
SkipList* skiplist_create(int (*precedes)(void*, void*)){
  SkipList* skip_list = (SkipList *)malloc(sizeof(SkipList));
   if (skip_list == NULL){
    fprintf(stderr, "SkipList_create: unable to allocate the memory\n");
    exit(EXIT_FAILURE);
  }
  skip_list->head = create_node(NULL, MAX_HEIGHT);
  skip_list->max_level = 0;
  skip_list->compare = precedes;
  return skip_list;
} 

/*
 * It creates the Node and it initialises it.
 */
Node* create_node(void* elem, int lvl){
  Node *new_node = malloc(sizeof(Node));
  new_node->size = lvl;
  new_node->item = elem;
  new_node->next = (Node **) malloc(sizeof(Node*) * new_node->size);
  for(int i = 0; i < new_node->size; i++){
	new_node->next[i] = NULL; 
  }
  return new_node;
}

void skiplist_insert(SkipList *list, void* elem){
  Node *new = create_node(elem, random_level());
  if(new->size > list->max_level)
    list->max_level = new->size;
  
  Node *tmp = list->head;
  for(int k = (list->max_level) -1; k >= 0; k--){ 
    if(tmp->next[k] == NULL || list->compare(elem, tmp->next[k]->item) < 0){
      if(k < (int)new->size){
        new->next[k] = tmp->next[k];
        tmp->next[k] = new;
      }
    }else{
      tmp = tmp->next[k];
      k++;
    }
  }
}

int random_level(){
  int lvl = 1;
  while((float)(rand()%100)/100 < 0.5 && lvl < MAX_HEIGHT)
    lvl++;

  return lvl;
}

void* skiplist_search(SkipList *list, void* item){
  Node *x = list->head;
  for(int i = (int)(list->max_level)-1; i >=0; i--){
    while(x->next[i] != NULL && list->compare(x->next[i]->item, item) < 0){
      x = x->next[i];
    }
  }
  x = x->next[0];
  if(x != NULL && list->compare(x->item, item) == 0)
      return x->item;

  return NULL; 
}


void skiplist_free(SkipList *list){
  if(list == NULL){
	  fprintf(stderr, "SkipList_free: unable to deallocate the memory\n");
	  exit(EXIT_FAILURE);
  }
  Node *tmp;
  while(list->head != NULL){
    tmp = list->head;
    list->head = list->head->next[0];
    node_Free(tmp);
  }
	free(list);
}

void node_Free(Node *node){
  free(node->item);
  free(node->next);
  free(node);
}
