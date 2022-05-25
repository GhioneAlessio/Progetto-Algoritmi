#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#define MAX_HEIGHT 20 //numero massimo di puntatori che possono esserci in un singolo nodo della `skip_list`


typedef struct _SkipList SkipList;
typedef struct _Node Node;

struct _SkipList {
  Node *head;
  unsigned int max_level; //determina il massimo attuale tra i vari `size`
  int (*compare)(void*, void*);
};

struct _Node {
  Node **next;
  unsigned int size; // numero di puntatori in un dato nodo della `skip_list`
  void *item;
};

SkipList* skiplist_create(int (*precedes)(void*, void*));
Node* create_node(void* elem, int lvl);
int random_level();
void skiplist_insert(SkipList *list, void* elem);
void* skiplist_search(SkipList *list, void* item);
void skiplist_free(SkipList *skip_list, void (*free_elem)(void *));
void node_free(Node *node, void (*free_elem)(void *));
void print_list(SkipList *skip_list);
#endif