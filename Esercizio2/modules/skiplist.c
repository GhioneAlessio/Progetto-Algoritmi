#include <stdio.h>
#include <stdlib.h>
#include "skiplist.h"

SkipList* SkipList_create(int (*precedes)(void*, void*)){
  SkipList* skip_list = (SkipList *)malloc(sizeof(SkipList));
   if (skip_list == NULL){
    fprintf(stderr, "SkipList_create: unable to allocate the memory\n");
    exit(EXIT_FAILURE);
  }
  //skip_list->head = (Node *)malloc(sizeof(Node));
  skip_list->head = create_Node(NULL, MAX_HEIGHT);
  skip_list->max_level = 0;
  skip_list->compare = precedes;
  return skip_list;
} 

Node* create_Node(void* elem, int lvl){
  Node *new_node = malloc(sizeof(Node));
  new_node->size = lvl;
  new_node->item = elem;
  new_node->next = (Node **) malloc(sizeof(Node*) * new_node->size);//next[new_node->size];
  for(int i = 0; i < new_node->size; i++){
	new_node->next[i] = NULL; 
  }
  return new_node;
}

void SkipList_insert(SkipList *list, void* elem){
  Node *new = create_Node(elem, random_Level());
  if(new->size > list->max_level)
    list->max_level = new->size;
  
  Node *tmp = list->head;
  for(int k = (int)(list->max_level) -1; k >= 0; k--){
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

int random_Level(){
  int lvl = 1;
  while(random() < 0.5 && lvl < MAX_HEIGHT)
    lvl++;

  return lvl;
}

void* SkipList_search(SkipList *list, void* item){
  Node *x = list->head;
  for(int i = list->max_level; i > 1; i--){
    while(x->next[i]->item < item){
      x = x->next[i];
    }
  }
  x = x->next[1];
  if(x->item == item)
    return x->item;
  else 
    return NULL; 
}


void SkipList_free(SkipList *list){
  if(list == NULL){
	  fprintf(stderr, "SkipList_free: unable to allocate the memory");
	  exit(EXIT_FAILURE);
  }
  SkipList *tmp = list;
  while(tmp != NULL){
	Node_Free(list->head);
  }
	free(list);
}

void Node_Free(Node *node){
  free(node->item);
  free(node->next);
  free(node);
}
