#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#define MAX_HEIGHT 20//numero massimo di puntatori che possono esserci in un singolo nodo della `skip_list`


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

SkipList* SkipList_create(int (*precedes)(void*, void*));
Node* create_Node(void* elem, int lvl);
int random_Level();
void SkipList_insert(SkipList *list, void* elem);
void* SkipList_search(SkipList *list, void* item);
void SkipList_free(SkipList *skip_list);
void Node_Free(Node *node);
void print_list(SkipList *skip_list);
#endif