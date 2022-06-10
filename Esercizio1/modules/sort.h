#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#define LESS_THAN 1
#define EQUAL_TO 0
#define GREATER_THAN -1

typedef struct _Sort Sort;

struct _Sort{
  void** array; 
  unsigned long array_capacity;
  unsigned long size;
  int (*precedes)(void*, void*);
};

/* 
 * sort_create(): checks that parametres are not NULL and allocs memory 
 * for the data structure sort.
 * It then initialises the struct's fields. 
 */
Sort *sort_create (int (*qs_precedes)(void*, void*));

/*
 * sort_size(): checks if the struct is NULL, if it's not it returns
 * the size field.  
 */
unsigned long sort_size(Sort *);

/*
 * sort_add(): checks if either the data structure or the element parametre is null,
 * then reallocs memory to fit the new element. The capacity and size fields are updated 
 * and the element is inserted in its place.  
 */
void sort_add(Sort *, void*);

/* 
 * sort_get():returns the element at i index 
 */
void* sort_get(Sort *, unsigned long);

/*
 * sort_free_memory(): frees memory after checking whether the structure is NULL or not.
 */
void* sort_free_memory(Sort *, void(*free_elem) (void*));

/**********QUICKSORT**********/
/*
 * quick_sort: Check base condition, if parametres are correct 
 * partition is called and the result is stored. 
 * Then quick_sort is called on the subarrays.  
*/
void quick_sort(Sort *sort, int left, int right);

/* 
 * Partition using Hoare's Partitioning scheme 
 * This procedure uses two indices set at the beginning and at the end of the array.
 * They move towords each other until there's an inversion to be made. 
 * When the indices meet, the procedure stops and the last index is returned. 
 */
int partition(Sort *sort, int array_start, int array_end);

/**********BINARY INSERTION SORT**********/
/*  
 * insertion_sort: selected (item at i index) stores the element to be inserted. 
 * It then finds the location where selected should be inseretd by
 * calling binary_search(), then moves all elements after location to create space. 
 */
void insertion_sort (Sort *sort, int length);
/*   
 * binary_search: mid is set to *parte intera inferiore*. 
 * If item is in mid position, mid + 1 is returned,  else if item is
 * greater it sets low to mid + 1, then returns it.
 * It is returned the index where insertion_sort() will insert the element to order the data.  
 */
int binary_search(Sort *sort, void* target, int left, int right);

  
/*
 * swap(): swaps two elements. Needed by the quick_sort algorithm.
 */
void swap(Sort *sort, int p, int j);

#endif