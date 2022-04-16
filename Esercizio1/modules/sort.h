#ifndef QUICK_SORT_H
#define QUICK_SORT_H

typedef struct _QuickSort QuickSort;

struct _QuickSort{
	void** array; 
  unsigned long array_capacity;
	unsigned long size;
	int (*precedes)(void*, void*);
};

QuickSort *quick_sort_create (int (*qs_precedes)(void*, void*));
unsigned long quick_sort_size(QuickSort *);
void quick_sort_add(QuickSort *, void*);
void* quick_sort_get(QuickSort *, unsigned long);
void* quick_sort_free_memory(QuickSort *);

int partition(QuickSort *quick_sort, int array_start, int array_end);
void quickSort(QuickSort *quick_sort, int array_start, int array_end);

int binary_search(QuickSort *quick_sort, void* target, int left, int right);
void insertion_sort (QuickSort *quick_sort, int length);

void swap(QuickSort *quick_sort, int p, int j);

#endif