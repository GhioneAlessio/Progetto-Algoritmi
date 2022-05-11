#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../modules/unity.h"
#include "../modules/sort.h"

/*
 * Test suite
 */

/*
 * precedence relation used in tests
 */
static int precedes_int (void* i1_p, void* i2_p){
  int* int1_p = (int*) i1_p;
  int* int2_p = (int*) i2_p;
  if((*int1_p)<(*int2_p)) return(1);
  return(0);
}
static int precedes_char (void* c1_p, void* c2_p){
  char* char1_p = (char*) c1_p;
  char* char2_p = (char*) c2_p;
  if(strcmp(char1_p,char2_p)<0) return(1);
  return(0);
}

static int i1, i2, i3;
static Sort *sort_int;
static char *c1, *c2, *c3;
static Sort *sort_char;

void setUp(void){
  i1 = -12;
  i2 = 0;
  i3 = 4;
  sort_int = sort_create(precedes_int);
  c1 = "alpha";
  c2 = "beta";
  c3 = "gamma";
  sort_char = sort_create(precedes_char);
}

void tearDown(void){
  sort_free_memory(sort_int);
}

static void test_sort_size_zero_el(void){
  TEST_ASSERT_EQUAL_INT(0, sort_size(sort_int));
}

static void test_sort_size_one_int_el(void){
  sort_add(sort_int, &i1);
  TEST_ASSERT_EQUAL_INT(1, sort_size(sort_int));
}

static void test_sort_size_one_char_el(void){
  sort_add(sort_char, &c1);
  TEST_ASSERT_EQUAL_INT(1, sort_size(sort_char));
}

static void test_sort_size_two_int_el(void){
  sort_add(sort_int, &i1);
  sort_add(sort_int, &i2);
  TEST_ASSERT_EQUAL_INT(2, sort_size(sort_int));
}

static void test_sort_add_get_one_int_el(void){
  sort_add(sort_int, &i1);
  TEST_ASSERT_EQUAL_PTR(&i1,sort_get(sort_int,0));
}

static void test_sort_add_get_one_char_el(void){
  sort_add(sort_char, &c1);
  TEST_ASSERT_EQUAL_PTR(&c1,sort_get(sort_char,0));
}

static void test_sort_quicksort_three_int_el(void){
  int* sort_expected[] = {&i1,&i2,&i3};
  sort_add(sort_int, &i3);
  sort_add(sort_int, &i1);
  sort_add(sort_int, &i2);
  quick_sort(sort_int, 0, sort_size(sort_int)-1);
  int** sort_actual = malloc(3*sizeof(int*));
  for(unsigned long i=0;i<3;i++){
    sort_actual[i]=(int*)sort_get(sort_int, i);
  }
  TEST_ASSERT_EQUAL_PTR_ARRAY(sort_expected,sort_actual,3);
}

static void test_sort_insertionsort_three_int_el(void){
  int* sort_expected[] = {&i1,&i2,&i3};
  sort_add(sort_int, &i3);
  sort_add(sort_int, &i1);
  sort_add(sort_int, &i2);
  insertion_sort(sort_int, sort_size(sort_int)-1);
  int** sort_actual = malloc(3*sizeof(int*));
  for(unsigned long i=0;i<3;i++){
    sort_actual[i]=(int*)sort_get(sort_int, i);
  }
  TEST_ASSERT_EQUAL_PTR_ARRAY(sort_expected,sort_actual,3);
}

static void test_sort_quicksort_three_char_el(void){
  char** sort_expected[] = {&c1,&c2,&c3};
  sort_add(sort_char, &c3);
  sort_add(sort_char, &c1);
  sort_add(sort_char, &c2);
  quick_sort(sort_char, 0, sort_size(sort_char)-1);
  char** sort_actual = malloc(3*sizeof(char*));
  for(unsigned long i=0;i<3;i++){
    sort_actual[i]=(char*)sort_get(sort_char, i);
  }
  TEST_ASSERT_EQUAL_PTR_ARRAY(sort_expected,sort_actual,3);
}

static void test_sort_insertionsort_three_char_el(void){
  char** sort_expected[] = {&c1,&c2,&c3};
  sort_add(sort_char, &c3);
  sort_add(sort_char, &c1);
  sort_add(sort_char, &c2);
  insertion_sort(sort_char, sort_size(sort_char)-1);
  char** sort_actual = malloc(3*sizeof(char*));
  for(unsigned long i=0;i<3;i++){
    sort_actual[i]=(char*)sort_get(sort_char, i);
  }
  TEST_ASSERT_EQUAL_PTR_ARRAY(sort_expected,sort_actual,3);
}

int main(void){
  
  UNITY_BEGIN();

  RUN_TEST(test_sort_size_zero_el);
  RUN_TEST(test_sort_size_one_int_el);
  RUN_TEST(test_sort_size_one_char_el);  
  RUN_TEST(test_sort_size_two_int_el);
  RUN_TEST(test_sort_add_get_one_int_el);
  RUN_TEST(test_sort_add_get_one_char_el);
  RUN_TEST(test_sort_quicksort_three_int_el);
  RUN_TEST(test_sort_insertionsort_three_int_el);
  RUN_TEST(test_sort_quicksort_three_char_el);
  RUN_TEST(test_sort_insertionsort_three_char_el);  

  return UNITY_END();

}
