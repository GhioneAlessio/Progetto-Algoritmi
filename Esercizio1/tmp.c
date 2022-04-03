
int binary_search ( int array[], int target, int left, int right) {
    if (left > right)
      return -1;
    else {
        int mid = (left + right) / 2;
        if (array[mid] == target)
           return mid;
        else if (array[mid] > target)
            return binary_search(array, target, left, mid - 1);
        else /* array[mid] < target */
           return binary_search(array, target, mid + 1, right); 
    }
}

void insertion_sort (int a[], int l){
	int i = 1;
	for(i = 1; i < l; i++){
		int j = i;
		while(j > 0 && a[j - 1] > a[j]){
			int tmp = a[j];
			a[j] = a[j-1];
			a[j-1] = tmp;
			j--;
		}
	
	}
}


void quickSort(int array[], int array_start, int array_end) {
  int pivot = 0;
  if (array_start < array_end) { 
    pivot = Partition(array, array_start, array_end);      
    if (pivot > 1)
      quickSort(array, array_start, pivot - 1);
    if (pivot < array_end - 1)
    quickSort(array, pivot + 1, array_end);
  }
}
  
int Partition(int array[], int array_start, int array_end) {
  int i = array_start+1, j = array_end;
  while (i <= j) {  
    if (array[i] <= array[array_start]) {
      i = i + 1;
    } else {
      if (array[j] > array[array_start]) {
        j = j - 1;
      } else {
        swap(array, i, j);
        i = i + 1;
        j = j - 1;
      }
    }
  }
  swap(array, array_start, j);
  return j;
}

void swap(int array[], int p, int j) {
  int tmp;
  tmp = array[p];
  array[p] = array[j];
  array[j] = tmp;
}
  
  
