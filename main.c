#include "hash.h"

#include <stdbool.h>
#include <assert.h>

/**
 * This file is to check list.h and list.c for part I of the assignment only
 *
 * Do not include it in the submission of part II
 *
 * You are expected to add additional test cases to this file
 * and to run valgrind on the program once you have it working
 */

//Tests that the hashcode function works
bool basicHashcode(hash_struct* table){


    if (hashcode(table, 7) == 7 && hashcode(table, 107) == 7){
        return true;
    } else {
        return false;
    }

}


//tests that an empty list has size == 0
bool testBasicEmpty(hash_struct* table){

    clear(table);

    if (isEmpty(table) == true){
        return true;
    } return false;

}

//tests put on empty table
bool testPutEmpty(hash_struct* table) {
  
  clear(table);
  
  put(table, 0, 10);
  if (table -> buckets[0] -> value == 10 && table -> buckets[0] -> key == 0) {
    return true;
  } return false;
  
}

//tests put on table filled
bool testPutShift(hash_struct* table) {
  
  clear(table);
  
  put(table, 0, 10);
  put(table, 100, 13);
  if (table -> buckets[1] -> value == 13 && table -> buckets[1] -> key == 100) {
    return true;
  } return false;
  
}

//tests get on table
bool testGet(hash_struct* table) {
  
  clear(table);
  
  put(table, 0, 10);
  data_entry* bucket = get(table, 0);
  if (bucket -> value == 10 && bucket -> key == 0) {
    return true;
  } return false;
  
}

//tests contain on table for both true and false
bool testContains(hash_struct* table) {
  
  clear(table);
  
  put(table, 0, 10);
  return (contains(table, 0) && !contains(table, 10));
  
}

//tests size for empty
bool testSizeEmpty(hash_struct* table) {
  
  clear(table);
  
  return (size(table) == 0);
  
}

//tests size for non-empty
bool testSizeNonEmpty(hash_struct* table) {
  
  clear(table);
  
  put(table, 0, 10);
  return (size(table) == 1);
  
}

//tests clear
bool testClear(hash_struct* table) {
  
  clear(table);
  
  put(table, 0, 10);
  clear(table);
  return isEmpty(table);
  
}

//tests remove entry from table
bool testRemove(hash_struct* table) {
  
  clear(table);
  
  put(table, 0, 10);
  removeEntry(table, 0);
  return isEmpty(table);
  
}





int main()
{
    printf ("Creating table\n") ;

    hash_struct* my_table = initTable(100) ;


    if (basicHashcode(my_table) == true){
        printf("%s\n", "Passed Test 1 : basicHashcode()");
    } else {
        printf("%s\n", "Failed Test 1 : basicHashcode()");
    }

    if (testBasicEmpty(my_table) == true){
        printf("%s\n", "Passed Test 2 : testBasicEmpty()");
    } else {
        printf("%s\n", "Failed Test 2 : testBasicEmpty()");
    }

    //-------------------YOU CAN ADD YOUR OWN TESTS HERE---------
      
    if (testPutEmpty(my_table) == true){
        printf("%s\n", "Passed Test 3 : testPutEmpty()");
    } else {
        printf("%s\n", "Failed Test 3 : testPutEmpty()");
    }
  
    if (testPutShift(my_table) == true){
        printf("%s\n", "Passed Test 4 : testPutShift()");
    } else {
        printf("%s\n", "Failed Test 4 : testPutShift()");
    }
  
    if (testGet(my_table) == true){
        printf("%s\n", "Passed Test 5 : testGet()");
    } else {
        printf("%s\n", "Failed Test 5 : testGet()");
    }
  
    if (testContains(my_table) == true){
        printf("%s\n", "Passed Test 6 : testContains()");
    } else {
        printf("%s\n", "Failed Test 6 : testContains()");
    }
  
    if (testSizeEmpty(my_table) == true){
        printf("%s\n", "Passed Test 7 : testSizeEmpty()");
    } else {
        printf("%s\n", "Failed Test 7 : testSizeEmpty()");
    }
  
    if (testSizeNonEmpty(my_table) == true){
        printf("%s\n", "Passed Test 8 : testSizeNonEmpty()");
    } else {
        printf("%s\n", "Failed Test 8 : testSizeNonEmpty()");
    }
  
    if (testClear(my_table) == true){
        printf("%s\n", "Passed Test 9 : testClear()");
    } else {
        printf("%s\n", "Failed Test 9 : testClear()");
    }
  
    if (testRemove(my_table) == true){
        printf("%s\n", "Passed Test 10 : testRemove()");
    } else {
        printf("%s\n", "Failed Test 10 : testRemove()");
    }


    //-------------------------------------------------


    printf ("freeing table\n") ;
    done(my_table) ;



    return 0;

}
