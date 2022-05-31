#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

#define INITIAL_CAPACITY_QS 2

/* 
 * sort_create(): checks that parametres are not NULL and allocs memory 
 * for the data structure sort.
 * It then initialises the struct's fields. 
 */
Sort *sort_create(int (*qs_precedes)(void *, void *)){	
  if (qs_precedes == NULL){
	  fprintf(stderr, "sort_create: precedes parameter cannot be NULL");
	  exit(EXIT_FAILURE);
	}
  Sort *sort = (Sort *)malloc(sizeof(Sort));
  if (sort == NULL){
    fprintf(stderr, "sort_create: unable to allocate the memory");
    exit(EXIT_FAILURE);
  }
  sort->array = (void **)malloc(INITIAL_CAPACITY_QS * sizeof(void *));
  if (sort->array == NULL){
    fprintf(stderr, "sort_create: unable to allocate the memory for the internal array");
    exit(EXIT_FAILURE);
  }
  sort->size = 0;
  sort->array_capacity = INITIAL_CAPACITY_QS;
  sort->precedes = qs_precedes;
  return sort;
}

/*
 * sort_size(): checks if the struct is NULL, if it's not it returns
 * the size field.  
 */
unsigned long sort_size(Sort *sort){	
  if (sort == NULL){
    fprintf(stderr, "sort_size: sort parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return sort->size;
}

/*
 * sort_add(): checks if either the data structure or the element parametre is null,
 * then reallocs memory to fit the new element. The capacity and size fields are updated 
 * and the element is inserted in its place.  
 */
void sort_add(Sort *sort, void *element){	
  if (sort == NULL){
    fprintf(stderr, "sort_add: sort parameter cannot be NULL\n");
    exit(EXIT_FAILURE);
  }
  if (element == NULL){
    fprintf(stderr, "sort_add: element parameter cannot be NULL\n");
    exit(EXIT_FAILURE);
  }
  if (sort->size >= sort->array_capacity){
    sort->array = (void **)realloc(sort->array, 2 * (sort->array_capacity) * sizeof(element));
    if (sort->array == NULL){
      fprintf(stderr, "sort_add: unable to reallocate the memory to host the new element\n");
      exit(EXIT_FAILURE);
    }
    sort->array_capacity = 2 * sort->array_capacity;
  }
  (sort->array)[sort->size] = element;
  (sort->size)++;
}

/* 
 * sort_get():returns the element at i index.
 */
void *sort_get(Sort *sort, unsigned long i){	
  if (sort == NULL){
    fprintf(stderr, "sort_get: unable to allocate the memory");
    exit(EXIT_FAILURE);
  }
  if (i >= sort->size){
    fprintf(stderr, "sort_get: index %lu out of bounds", i);
    exit(EXIT_FAILURE);
	}
  return sort->array[i];
}

/*
 * sort_free_memory(): frees memory after checking whether the structure is NULL or not.
 */
void *sort_free_memory(Sort *sort){	
  if (sort == NULL){
    fprintf(stderr, "sort_free_memory: unable to allocate the memory");
    exit(EXIT_FAILURE);
  }
  free(sort->array);
  free(sort);
}

/*** Quicksort ***/
/*
 * quick_sort: Check base condition, if parametres are correct 
 * partition is called and the result is stored. 
 * Then quick_sort is called on the subarrays.  
*/
void quick_sort(Sort *sort, int left, int right){
  if(left < right){
    int p = partition(sort, left, right);
    quick_sort(sort, left, p);
    quick_sort(sort, p + 1, right);
  }
}

/* 
 * Partition using Hoare's Partitioning scheme 
 * This procedure uses two indices set at the beginning and at the end of the array.
 * They move towords each other until there's an inversion to be made. 
 * When the indices meet, the procedure stops and the last index is returned. 
 */
int partition(Sort *sort, int array_start, int array_end){	
  void** pivot;
  pivot = sort->array[(array_end + array_start)/2];
  swap(sort, array_start, (array_end + array_start)/2);
  int i = array_start - 1;
  int j = array_end + 1;
  while (1){
    do{
      i++;
    } while (sort->precedes(sort->array[i], pivot) == LESS_THAN);
    do{
      j--;
    } while (sort->precedes(sort->array[j], pivot) == GREATER_THAN);
    if (i >= j){
      return j;
    }
    swap(sort, i, j);
  }
}

/*** Binary Insertion Sort ***/
/*   
 * binary_search: mid is mapped to the least integer greater than or 
 * equal to x, by the ceiling function. 
 * If item is in mid position, mid + 1 is returned,  else if item is
 * greater it sets low to mid + 1, then returns it.
 * It is returned the index where insertion_sort() will insert the 
 * element to order the data.  
 */
int binary_search(Sort *sort, void *item, int left, int right){	
  while (left <= right){
    int mid = left + (right - left) / 2;
    if ((sort->precedes(sort->array[mid], item) == EQUAL_TO))
      return mid + 1;
    else if (sort->precedes(item, sort->array[mid]) == GREATER_THAN)  
      left = mid + 1;
    else
      right = mid - 1;
  }
  return left;
}

/*  
 * insertion_sort: selected (item at i index) stores the element to be inserted. 
 * It then finds the location where selected should be inseretd by
 * calling binary_search(), then moves all elements after location to create space. 
 */
void insertion_sort(Sort *sort, int length){	
  int i, loc, j, k;
  void *selected; 
  for (i = 1; i <= length; i++) {
    j = i - 1;
    selected = sort->array[i];
    loc = binary_search(sort, selected, 0, j);
    while (j >= loc) {
      sort->array[j + 1] =  sort->array[j];
      j--;
    }
    sort->array[j + 1] = selected;
  }
}

/*
 * swap(): swaps two elements. Needed by the quick_sort algorithm.
 */
void swap(Sort *sort, int a, int b){	
  void **tmp;
  tmp = sort->array[a];
  sort->array[a] = sort->array[b];
  sort->array[b] = tmp;
}