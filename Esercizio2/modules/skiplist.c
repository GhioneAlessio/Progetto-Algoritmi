#include <stdio.h>
#include <stdlib.h>
#include "skiplist.h"

SkipList* SkipList_create(int (*precedes)(void*, void*)){
  SkipList* skip_list = (SkipList *)malloc(sizeof(SkipList));
   if (skip_list == NULL){
    fprintf(stderr, "SkipList_create: unable to allocate the memory\n");
    exit(EXIT_FAILURE);
  }
  skip_list->head = (Node *)malloc(sizeof(Node));
  skip_list->max_level = skip_list->head->size;
  skip_list->compare = precedes;
} 

Node* create_Node(void* elem, int lvl){
  Node *new_node = malloc(sizeof(Node));
  new_node->size = lvl;
  new_node->item = malloc(sizeof(elem));
  new_node->next[new_node->size];
  return new_node;
}

void SkipList_insert(SkipList *list, void* elem){
  Node *new = create_Node(elem, random_Level());
  if(new->size > list->max_level)
    list->max_level = new->size;
  
  Node *tmp = list->head;
  for(int k = list->max_level; k > 1;){
    if(tmp->next[k] == NULL || elem < tmp->next[k]->item){
      if(k < new->size){
        new->next[k] = tmp->next[k];
        tmp->next[k] = new;
      }else{
        tmp = tmp->next[k];
        k++;
      }
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

//
void SkipList_free(SkipList *list){
	if(list == NULL)
	{
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

}


/*
insertSkipList: Inserisce I nella skiplist ``list``
insertSkipList(list, I)

    new = createNode(I, randomLevel())
    if new->size > list->max_level
        list->max_level = new->size

    x = list->head
    for k = list->max_level downto 1 do
        if (x->next[k] == NULL || I < x->next[k]->item)
            if k < new->size {
              new->next[k] = x->next[k]
              x->next[k] = new
            }
        else
            x = x->next[k]
```

La funzione ``randomLevel()`` determina il numero di puntatori da includere nel nuovo nodo e deve essere realizzata conformemente al seguente algoritmo. Spiegare il vantaggio di questo algoritmo nella relazione da consegnare con l'esercizio:
```
randomLevel()
    lvl = 1

    // random() returns a random value in [0...1)
    while random() < 0.5 and lvl < MAX_HEIGHT do
        lvl = lvl + 1
    return lvl
```

#####  searchSkipList: Verifica se I è presente nella skiplist list
```
searchSkipList(list, I)
    x = list->head

    // loop invariant: x->item < I
    for i = list->max_level downto 1 do
        while x->next[i]->item < I do
            x = x->next[i]

    // x->item < I <= x->next[1]->item
    x = x->next[1]
    if x->item == item then
        return x->item
    else
        return failure
*/