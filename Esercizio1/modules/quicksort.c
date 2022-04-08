#include <stdlib.h>
#include <stdio.h>
#include "quicksort.h"

#define INITIAL_CAPACITY_QS 2

static unsigned long get_index_to_insert_qs(QuickSort *quick_sort, void *element);
static void insert_element_qs(QuickSort *quick_sort, void *element, unsigned long index);

QuickSort *quick_sort_create(int (*qs_precedes)(void *, void *))
{
	if (qs_precedes == NULL)
	{
		fprintf(stderr, "quick_sort_create: precedes parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	QuickSort *quick_sort = (QuickSort *)malloc(sizeof(QuickSort));
	if (quick_sort == NULL)
	{
		fprintf(stderr, "quick_sort_create: unable to allocate the memory");
		exit(EXIT_FAILURE);
	}
	quick_sort->array = (void **)malloc(INITIAL_CAPACITY_QS * sizeof(void *));
	if (quick_sort->array == NULL)
	{
		fprintf(stderr, "quick_sort_create: unable to allocate the memory for the internal array");
		exit(EXIT_FAILURE);
	}
	quick_sort->size = 0;
	quick_sort->array_capacity = INITIAL_CAPACITY_QS;
	quick_sort->precedes = qs_precedes;
	return quick_sort;
}

int quick_sort_is_empty(QuickSort *quick_sort)
{
	if (quick_sort == NULL)
	{
		fprintf(stderr, "quick_sort_is_empty: quick_sort parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	if (quick_sort->size == 0)
		return 1;
	return 0;
}

unsigned long quick_sort_size(QuickSort *quick_sort)
{
	if (quick_sort == NULL)
	{
		fprintf(stderr, "quick_sort_size: quick_sort parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	return quick_sort->size;
}

void quick_sort_add(QuickSort *quick_sort, void *element)
{
	if (quick_sort == NULL)
	{
		fprintf(stderr, "quick_sort_add: quick_sort parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	if (element == NULL)
	{
		fprintf(stderr, "quick_sort_add: element parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	if (quick_sort->size >= quick_sort->array_capacity)
	{
		quick_sort->array = (void **)realloc(quick_sort->array, 2 * (quick_sort->array_capacity) * sizeof(void *));
		if (quick_sort->array == NULL)
		{
			fprintf(stderr, "quick_sort_add: unable to reallocate the memory to host the new element");
			exit(EXIT_FAILURE);
		}
		quick_sort->array_capacity = 2 * quick_sort->array_capacity;
	}
	(quick_sort->array)[quick_sort->size] = element;
	(quick_sort->size)++;
}

void *quick_sort_get(QuickSort *quick_sort, unsigned long i)
{
	if (quick_sort == NULL)
	{
		fprintf(stderr, "quick_sort_get: unable to allocate the memory");
		exit(EXIT_FAILURE);
	}
	if (i >= quick_sort->size)
	{
		fprintf(stderr, "quick_sort_get: index %lu out of bounds", i);
		exit(EXIT_FAILURE);
	}
	return (quick_sort->array)[i];
}

void *quick_sort_free_memory(QuickSort *quick_sort)
{
	if (quick_sort == NULL)
	{
		fprintf(stderr, "quick_sort_free_memory: unable to allocate the memory");
		exit(EXIT_FAILURE);
	}
	free(quick_sort->array);
	free(quick_sort);
}

void swap(QuickSort *quick_sort, int p, int j)
{
	void **tmp;
	tmp = quick_sort->array[p];
	quick_sort->array[p] = quick_sort->array[j];
	quick_sort->array[j] = tmp;
}

void quickSort(QuickSort *quick_sort, int array_start, int array_end, void (*print)(void *))
{
	printf("quicksort\n");
	int pivot = 0;
	if (array_start < array_end)
	{
		pivot = Partition(quick_sort, array_start, array_end, print);
		if (pivot > 1)
			quickSort(quick_sort, array_start, pivot - 1, print);
		if (pivot < array_end - 1)
			quickSort(quick_sort, pivot + 1, array_end,print);
	}
}

int Partition(QuickSort *quick_sort, int array_start, int array_end, void (*print)(void *))
{
	int tmp;
	int i = array_start + 1, j = array_end - 1;
	while (i <= j)
	{// array[i] <= array[array_start]
		if ((quick_sort->precedes(quick_sort->array[i], quick_sort->array[array_start]) ||
				 (!(quick_sort->precedes(quick_sort->array[i], quick_sort->array[array_start])) && !(quick_sort->precedes(quick_sort->array[array_start], quick_sort->array[i])))) != 0)
		{
			i = i + 1;
		}
		else
		{//array[j] > array[array_start]
			if (quick_sort->precedes(quick_sort->array[array_start], quick_sort->array[j]))
			{
				j = j - 1;
			}
			else
			{
				swap(quick_sort, i, j);
				i = i + 1;
				j = j - 1;
			}
		}
	}
	swap(quick_sort, array_start, j);
	print(quick_sort);
	return j;
}
// quick_sort->array[i] <= quick_sort->array[array_start] primo if

// quick_sort->array[j] > quick_sort->array[array_start]  secondo if
