#ifndef QUICK_SORT_H
#define QUICK_SORT_H

typedef struct _QuickSort QuickSort;

QuickSort * quick_sort_create (int (*qs_precedes)(void*, void*));
int quick_sort_is_empty(QuickSort *);
unsigned long quick_sort_size(QuickSort *);
void quick_sort_add(QuickSort *, void*);
void* quick_sort_get(QuickSort *, unsigned long);
void* quick_sort_free_memory(QuickSort *);

#endif

int qs_precedes(int *a, int *b);
int Partition(int array[], int array_start, int array_end);
void quickSort (int array[], int array_start, int array_end);

void swap (int array[], int p, int j);