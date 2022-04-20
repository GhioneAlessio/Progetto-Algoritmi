#ifndef QUICK_SORT_H
#define QUICK_SORT_H

typedef struct _Sort Sort;

struct _Sort{
  void** array; 
  unsigned long array_capacity;
  unsigned long size;
  int (*precedes)(void*, void*);
};

Sort *sort_create (int (*qs_precedes)(void*, void*));
unsigned long sort_size(Sort *);
void sort_add(Sort *, void*);
void* sort_get(Sort *, unsigned long);
void* sort_free_memory(Sort *);

int partition(Sort *sort, int array_start, int array_end);
void quickSort(Sort *sort, int array_start, int array_end);

int binary_search(Sort *sort, void* target, int left, int right);
void insertion_sort (Sort *sort, int length);

void swap(Sort *sort, int p, int j);

#endif
