
void* quicksort (void* data, void* condition){

}

/*Condition: criteria to order the data*/

void* insertionsort ( ) {

}

int binarysearch ( int array[], int target, int left, int right) {
	if (left > right)
      return -1;
    else {
        int mid = (left + right) / 2;
        if (array[mid] == target)
           return mid;
        else if (array[mid] > target)
            return binarysearch(array, target, mid + 1, right);
        else /* array[mid] < target */
           return binarysearch(array, target, left, mid - 1);
    }
}
