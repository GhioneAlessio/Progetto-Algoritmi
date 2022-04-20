#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

#define INITIAL_CAPACITY_QS 2

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

unsigned long sort_size(Sort *sort){	
  if (sort == NULL){
    fprintf(stderr, "sort_size: sort parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return sort->size;
}

void sort_add(Sort *sort, void *element){	
  if (sort == NULL){
    fprintf(stderr, "sort_add: sort parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (element == NULL){
    fprintf(stderr, "sort_add: element parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (sort->size >= sort->array_capacity){
    sort->array = (void **)realloc(sort->array, 2 * (sort->array_capacity) * sizeof(element));
    if (sort->array == NULL){
      fprintf(stderr, "sort_add: unable to reallocate the memory to host the new element");
      exit(EXIT_FAILURE);
    }
    sort->array_capacity = 2 * sort->array_capacity;
  }
  (sort->array)[sort->size] = element;
  (sort->size)++;
}

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

void *sort_free_memory(Sort *sort){	
  if (sort == NULL){
    fprintf(stderr, "sort_free_memory: unable to allocate the memory");
    exit(EXIT_FAILURE);
  }
  free(sort->array);
  free(sort);
}

void swap(Sort *sort, int p, int j){	
  void **tmp;
  tmp = sort->array[p];
  sort->array[p] = sort->array[j];
  sort->array[j] = tmp;
}

/*** Quicksort ***/

void quick_sort(Sort *sort, int low, int high){
  // base condition
  if (low >= high){
    return;
  }
  // rearrange elements across pivot
  int pivot = partition(sort, low, high); 
  // recur on subarray containing elements that are less than the pivot
  quick_sort(sort, low, pivot);
  // recur on subarray containing elements that are more than the pivot
  quick_sort(sort, pivot + 1, high);
}
/*
void quick_sort(Sort *sort, int array_start, int array_end){
  while (array_start < array_end){
    int pivot = partition(quick_sort, array_start, array_end);
    if (pivot - array_start < array_end - pivot){
      quickSort(quick_sort, array_start, pivot - 1);
      array_start = pivot + 1;
    }
    else{
      quickSort(quick_sort, pivot + 1, array_end);
      array_end = pivot - 1;
    }
  }
}*/
/*
int partition(Sort *sort, int array_start, int array_end){
  int i = array_start + 1, j = array_end, tmp;
  while (i <= j){ // array[i] <= array[array_start]
    tmp = (sort->precedes(sort->array[i], sort->array[array_start]));
    if ( tmp || (!(tmp) && !(sort->precedes(sort->array[array_start], sort->array[i]) == 1))){
      i = i + 1;
    }
    else{//array[j] > array[array_start]
      if (sort->precedes(sort->array[array_start], sort->array[j]) == 1){
        j = j - 1;
      }
      else{
        swap(sort, i, j);
        i = i + 1;
        j = j - 1;
      }
    }
  }
  swap(sort, array_start, j);
  return j;
}*/

// Partition using Hoare's Partitioning scheme
int partition(Sort *sort, int array_start, int array_end){	
  int i = array_start - 1;
  int j = array_end + 1;
  while (1){
    do{
      i++;
    } while (sort->precedes(sort->array[i], sort->array[array_start]));
    do{
      j--;
    } while (sort->precedes(sort->array[array_start], sort->array[j]));
    if (i >= j){
      return j;
    }
    swap(sort, i, j);
  }
}

/*** Binary Insertion Sort ***/
int binary_search(Sort *sort, void *item, int low, int high){	
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (/*item == a[mid]*/((sort->precedes(sort->array[mid], item) && sort->precedes(item, sort->array[mid]))!= 0))
      return mid + 1;
    else if (/*item > a[mid]*/ sort->precedes(sort->array[mid], item) == 1)  
      low = mid + 1;
    else
      high = mid - 1;
  }
  return low;
}

void insertion_sort(Sort *sort, int n){	
  int i, loc, j, k;
  void *selected; 
  for (i = 1; i <= n; ++i) {
    j = i - 1;
    selected = sort->array[i];
    // find location where selected should be inseretd
    loc = binary_search(sort, selected, 0, j);
    // Move all elements after location to create space
    while (j >= loc) {
      sort->array[j + 1] =  sort->array[j];
      j--;
    }
    sort->array[j + 1] = selected;
  }
}
