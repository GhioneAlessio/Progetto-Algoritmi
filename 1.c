#include <stdio.h>
#include "EX1.h"

int main () {
  int[] array = {1,3,5,7,2,4,6,8};
  int r = binarysearch(array, 7, 0, 8);
  printf( "%d", r);
}