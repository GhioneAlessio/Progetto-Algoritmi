#include <stdlib.h>
#include <stdio.h>
#include "header.h"

#define INITIAL_CAPACITY_BIS 	2

/****************************************************************************************************************************/

static unsigned long get_index_to_insert_bis (BinaryInsertionSort * binary_insertion_sort, void* element);
static void insert_element_bis (BinaryInsertionSort * binary_insertion_sort, void* element, unsigned long index);

struct _BinaryInsertionSort{
	void **array; 
  	unsigned long array_capacity; 
	unsigned long size;
	int (*precedes)(void*, void*);
}

BinaryInsertionSort *binary_insertion_sort_create (int (*qs_precedes)(void*, void*)){
	if (precedes == NULL){
		fprintf(stderr, "binary_insertion_sort_create: precedes parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	BinaryInsertionSort * binary_insertion_sort = *binary_insertion_sort = (BinaryInsertionSort*) malloc (sizeof(BinaryInsertionSort));
	if (binary_insertion_sort == NULL){
		fprintf(stderr, "binary_insertion_sort_create: unable to allocate the memory");
		exit(EXIT_FAILURE);
	}
	binary_insertion_sort->array = (void**) malloc(INITIAL_CAPACITY * sizeof(void*));
	if (binary_insertion_sort->array == NULL){
		fprintf(stderr, "binary_insertion_sort_create: unable to allocate the memory for the internal array");
		exit(EXIT_FAILURE);
	}
	binary_insertion_sort->size = 0;
	binary_insertion_sort->array_capacity = INITIAL_CAPACITY;
	binary_insertion_sort->precedes = precedes;
	return binary_insertion_sort;
}

int binary_insertion_sort_is_empty(BinaryInsertionSort *binary_insertion_sort){
	if (binary_insertion_sort == NULL){
		fprintf(stderr, "binary_insertion_sort_is_empty: binary_insertion_sort parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	if (binary_insertion_sort->size == 0)
		return 1;
	return 0;
}

unsigned long binary_insertion_sort_size (BinaryInsertionSort *binary_insertion_sort){
	if (binary_insertion_sort == NULL){
		fprintf(stderr, "binary_insertion_sort_size: binary_insertion_sort parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	return binary_insertion_sort->size;
}

void binary_insertion_sort_add (BinaryInsertionSort *binary_insertion_sort, void* element){
	if (binary_insertion_sort == NULL){
		fprintf(stderr, "binary_insertion_sort_add: binary_insertion_sort parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	if (element == NULL){
		fprintf(stderr, "binary_insertion_sort_add: element parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	if(binary_insertion_sort->size >= binary_insertion_sort->array_capacity){
		binary_insertion_sort->array = (void**) realloc(binary_insertion_sort->array, 2*(binary_insertion_sort->array_capacity)*sizeof(void*));
		if (binary_insertion_sort->array == NULL){
			fprintf(stderr, "binary_insertion_sort_add: unable to reallocate the memory to host the new element");
			exit(EXIT_FAILURE);
		}
		binary_insertion_sort->array_capacity = 2* binary_insertion_sort->array_capacity; 
	}
	unsigned long index = get_index_to_insert_bis (binary_insertion_sort, element);
	insert_element_bis (binary_insertion_sort, element, index);
	(binary_insertion_sort->size)++;
}

void* binary_insertion_sort_get (BinaryInsertionSort *binary_insertion_sort, unsigned long i){
	if (binary_insertion_sort == NULL){
		fprintf(stderr, "binary_insertion_sort_get: unable to allocate the memory");
		exit(EXIT_FAILURE);
	}
	if (i >=binary_insertion_sort->size){
		fprintf(stderr, "binary_insertion_sort_get: index %lu out of bounds", i);
		exit(EXIT_FAILURE);
	}
	return (binary_insertion_sort->array)[i];
}

void* binary_insertion_sort_free_memory (BinaryInsertionSort *binary_insertion_sort){
	if (binary_insertion_sort == NULL){
		fprintf(stderr, "binary_insertion_sort_free_memory: unable to allocate the memory");
		exit(EXIT_FAILURE);
	}
	free(binary_insertion_sort->array);
	free(binary_insertion_sort);
}

static unsigned long get_index_to_insert_bis (BinaryInsertionSort * binary_insertion_sort, void* element){
	unsigned long i = 0;
	int cont = 1;
	while (i < binary_insertion_sort->size && cont){
		if((*(binary_insertion_sort->precedes))(element, (binary_insertion_sort->array)[i])){
			cont = 0;
		} else
			i++;
	}
	return i;
}

static void insert_element_bis (BinaryInsertionSort * binary_insertion_sort, void* element, unsigned long index){
	unsigned long i;
	for (i = binary_insertion_sort->size; i > index; i--){
		(binary_insertion_sort->array)[i] = (binary_insertion_sort->array)[i - 1];
	}
	(binary_insertion_sort->array)[index] = element; 
}

