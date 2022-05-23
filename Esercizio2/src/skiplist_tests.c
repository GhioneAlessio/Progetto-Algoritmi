#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../modules/unity.h"
#include "../modules/skiplist.h"

/*
 * Test suite
 */

/*
 * precedence relation used in tests
 */
static int precedes_int(void* i1_p, void* i2_p){
  int* int1_p = (int*) i1_p;
  int* int2_p = (int*) i2_p;
  if((*int1_p)<(*int2_p)) return(1);
  else if((*int1_p)==(*int2_p)) return(0);
  else return(-1);
}
static int precedes_float(void* f1_p, void* f2_p){
  float* float1_p = (float*) f1_p;
  float* float2_p = (float*) f2_p;
  if((*float1_p)<(*float2_p)) return(1);
  else if((*float1_p)==(*float2_p)) return(0);
  else return(-1);
}
static int precedes_char (void* c1_p, void* c2_p){
  char* char1_p = (char*) c1_p;
  char* char2_p = (char*) c2_p;
  return strcmp(char1_p,char2_p);
}

static int i1, i2, i3;
static SkipList *skiplist_int;
static float f1, f2, f3;
static SkipList *skiplist_float;
static char *c1, *c2, *c3;
static SkipList *skiplist_char;

void setUp(void){
  i1 = -12;
  i2 = 0;
  i3 = 4;
  skiplist_int = skiplist_create(precedes_int);
  f1 = -5.0294;
  f2 = 0.00003;
  f3 = 13.0;
  skiplist_float = skiplist_create(precedes_float);
  c1 = "alpha";
  c2 = "beta";
  c3 = "gamma";
  skiplist_char = skiplist_create(precedes_char);
}

void tearDown(void){
//  skiplist_free(skiplist_int);
//  skiplist_free(skiplist_float);
//  skiplist_free(skiplist_char);
}

static void test_skiplist_insert_one_search_one_int_el(){
  skiplist_insert(skiplist_int, &i1);
  TEST_ASSERT_EQUAL(skiplist_search(skiplist_int,&i1), &i1);
}

static void test_skiplist_insert_one_search_one_float_el(){
  skiplist_insert(skiplist_float, &f1);
  TEST_ASSERT_EQUAL(skiplist_search(skiplist_float,&f1), &f1);
}

static void test_skiplist_insert_one_search_one_char_el(){
  skiplist_insert(skiplist_char, &c1);
  TEST_ASSERT_EQUAL(skiplist_search(skiplist_char,&c1), &c1);
}

static void test_skiplist_insert_three_search_one_int_el(){
  skiplist_insert(skiplist_int, &i3);
  skiplist_insert(skiplist_int, &i1);
  skiplist_insert(skiplist_int, &i2);
  TEST_ASSERT_EQUAL(skiplist_search(skiplist_int,&i1), &i1);
}

static void test_skiplist_insert_three_search_one_float_el(){
  skiplist_insert(skiplist_float, &f3);
  skiplist_insert(skiplist_float, &f1);
  skiplist_insert(skiplist_float, &f2);
  TEST_ASSERT_EQUAL(skiplist_search(skiplist_float,&f1), &f1);
}

static void test_skiplist_insert_three_search_one_char_el(){
  skiplist_insert(skiplist_char, &c3);
  skiplist_insert(skiplist_char, &c1);
  skiplist_insert(skiplist_char, &c2);
  TEST_ASSERT_EQUAL(skiplist_search(skiplist_char,&c1), &c1);
}

static void test_skiplist_insert_search_not_found_int_el(){
  skiplist_insert(skiplist_int, &i1);
  TEST_ASSERT_NOT_EQUAL(skiplist_search(skiplist_int,&i2), &i1);
}

static void test_skiplist_insert_search_not_found_float_el(){
  skiplist_insert(skiplist_float, &f1);
  TEST_ASSERT_NOT_EQUAL(skiplist_search(skiplist_float,&f2), &f1);
}

static void test_skiplist_insert_search_not_found_char_el(){
  skiplist_insert(skiplist_char, &c1);
  TEST_ASSERT_NOT_EQUAL(skiplist_search(skiplist_char,&c2), &c1);
}

static void test_skiplist_search_empty_list_int_el(){
  TEST_ASSERT_NOT_EQUAL(skiplist_search(skiplist_int,&i1), &i1);
}

int main(void){
  
  UNITY_BEGIN();
  
  RUN_TEST(test_skiplist_insert_one_search_one_int_el);
  RUN_TEST(test_skiplist_insert_one_search_one_float_el);
  RUN_TEST(test_skiplist_insert_one_search_one_char_el);
  RUN_TEST(test_skiplist_insert_three_search_one_int_el);
  RUN_TEST(test_skiplist_insert_three_search_one_float_el);
  RUN_TEST(test_skiplist_insert_three_search_one_char_el);
  RUN_TEST(test_skiplist_insert_search_not_found_int_el);
  RUN_TEST(test_skiplist_insert_search_not_found_float_el);
  RUN_TEST(test_skiplist_insert_search_not_found_char_el);
  RUN_TEST(test_skiplist_search_empty_list_int_el);

  return UNITY_END();

}
