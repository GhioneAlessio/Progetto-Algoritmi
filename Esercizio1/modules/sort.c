#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

#define INITIAL_CAPACITY_QS 2

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
		quick_sort->array = (void **)realloc(quick_sort->array, 2 * (quick_sort->array_capacity) * sizeof(element));
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
	return quick_sort->array[i];
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

/*** Quicksort ***/

void quickSort(QuickSort *quick_sort, int low, int high)
{
    // base condition
    if (low >= high) {
        return;
    }
 
    // rearrange elements across pivot
    int pivot = partition(quick_sort, low, high);
 
    // recur on subarray containing elements that are less than the pivot
    quickSort(quick_sort, low, pivot);
 
    // recur on subarray containing elements that are more than the pivot
    quickSort(quick_sort, pivot + 1, high);
}
/*
void quickSort(QuickSort *quick_sort, int array_start, int array_end)
{
	while (array_start < array_end)
	{
		int pivot = partition(quick_sort, array_start, array_end);
		if (pivot - array_start < array_end - pivot)
		{
			quickSort(quick_sort, array_start, pivot - 1);
			array_start = pivot + 1;
		}
		else
		{
			quickSort(quick_sort, pivot + 1, array_end);
			array_end = pivot - 1;
		}
	}
}*/
/*
int partition(QuickSort *quick_sort, int array_start, int array_end)
{
	int i = array_start + 1, j = array_end, tmp;
	while (i <= j)
	{// array[i] <= array[array_start]
		tmp = (quick_sort->precedes(quick_sort->array[i], quick_sort->array[array_start]));
		if ( tmp ||
				 (!(tmp) && !(quick_sort->precedes(quick_sort->array[array_start], quick_sort->array[i]) == 1)))
		{
			i = i + 1;
		}
		else
		{//array[j] > array[array_start]
			if (quick_sort->precedes(quick_sort->array[array_start], quick_sort->array[j]) == 1)
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
	return j;
}*/

// Partition using Hoare's Partitioning scheme
int partition(QuickSort *quick_sort, int array_start, int array_end)
{
	int i = array_start - 1;
	int j = array_end + 1;
	while (1)
	{
		do
		{
			i++;
		} while (quick_sort->precedes(quick_sort->array[i], quick_sort->array[array_start]));
		do
		{
			j--;
		} while (quick_sort->precedes(quick_sort->array[array_start], quick_sort->array[j]));

		if (i >= j)
		{
			return j;
		}

		swap(quick_sort, i, j);
	}
}

/*** Binary Insertion Sort ***/
int binary_search(QuickSort *quick_sort, void *item, int low, int high)
{
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (/*item == a[mid]*/((quick_sort->precedes(quick_sort->array[mid], item) && quick_sort->precedes(item, quick_sort->array[mid]))!= 0))
            return mid + 1;
        else if (/*item > a[mid]*/ quick_sort->precedes(quick_sort->array[mid], item) == 1)  
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low;
}

void insertion_sort(QuickSort *quick_sort, int n)
{
    int i, loc, j, k;
    void *selected; 
 
    for (i = 1; i <= n; ++i) {
        j = i - 1;
        selected = quick_sort->array[i];
 
        // find location where selected should be inseretd
        loc = binary_search(quick_sort, selected, 0, j);
 
        // Move all elements after location to create space
        while (j >= loc) {
            quick_sort->array[j + 1] =  quick_sort->array[j];
            j--;
        }
         quick_sort->array[j + 1] = selected;
    }
}
