
/************Prototypes***********/

void swap (int array[], int p, int j);

/***********************************************************************************************/

#ifndef BINARY_INSERTION_SORT_H
#define BINARY_INSERTION_SORT_H

typedef struct _BinaryInsertionSort BinaryInsertionSort;


BinaryInsertionSort * binary_insertion_sort_create (int (*bis_precedes)(void*, void*));
int binary_insertion_sort_is_empty(BinaryInsertionSort *);
unsigned long binary_insertion_sort_size(BinaryInsertionSort *);
void binary_insertion_sort_add(BinaryInsertionSort *, void*);
void* binary_insertion_sort_get(BinaryInsertionSort *, unsigned long);
void* binary_insertion_sort_free_memory(BinaryInsertionSort *);

#endif
/************Prototypes***********/
int bis_precedes(int *a, int *b);
int binarysearch ( int array[], int target, int left, int right);
void insertion_sort(int a[], int l);

