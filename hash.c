#include "hash.h"


/**
* @input - A number of buckets, the size to make the hash table.
* Should assign space for the hash_struct pointer, all buckets, and should
* initialize all entries as KEY = -1, VALUE = -1 to begin.
* 
*/

hash_struct* initTable(int num_of_buckets){
  int i = 0; // for loop counter
  
  hash_struct* newTable = malloc(sizeof(hash_struct)); // Allocate memory for hash_struct*
  
  if (newTable == NULL) { // Check if success
    fprintf(stderr, "Error: Unable to allocate memory for newTable\n");
    return NULL;
    
  }
  // Allocate memory for rest of fields
    newTable -> buckets = malloc(sizeof(data_entry*) * num_of_buckets);
    
    if (newTable -> buckets == NULL) { // Check if success
      fprintf(stderr, "Error: Unable to allocate memory for buckets\n");
      return NULL;
      
    }
    
    newTable -> num_of_buckets = num_of_buckets; // store number of buckets in table
    
    for (i = 0; i < num_of_buckets; i++) { // set each bucket keys and values to -1      
      // Allocate memory for specific data_entry
      newTable -> buckets[i] = malloc(sizeof(data_entry));
      
      if (newTable -> buckets[i] == NULL) { // Check if success
      fprintf(stderr, "Error: Unable to allocate memory for data_entry\n");
      return NULL;
      
    }
      newTable -> buckets[i] -> key = -1;
      newTable -> buckets[i] -> value = -1;
    }
    
    return(newTable); // Return pointer to newly made hash_struct pointer


}


/*
* @input : Some key value.
* @returns : The key value modulated by the size of the hash table.
*/

int hashcode(hash_struct* table, int key){
  
        return key % table -> num_of_buckets; // key % size

}

/*
* @input : Some key value, table pointer.
* @returns : The data entry if some matching (key, value) pair exists, otherwise returns NULL.
*/
data_entry* get(hash_struct* table, int key){
  int index = 0; // Counter for traversing buckets
  
  for (index = 0; index < table -> num_of_buckets; index++) { // traverse bucket
    if (table -> buckets[index] -> key == key) {
      return table -> buckets[index]; // Found matching data entry
    } else {
      continue;
    }
  }

  return NULL; // No match for any bucket

}

/*
* @input : Some key value, table pointer.
* @returns : True only if a valid key exists that maps to this value.
*/
bool contains(hash_struct* table, int key){
  int index = 0; // Counter for traversing buckets
  
  for (index = 0; index < table -> num_of_buckets; index++) { // traverse bucket
    if (table -> buckets[index] -> key == key) {
      return true; // Found key value
    } else {
      continue;
    }
  }

  return false; // No match for any key


}

/*
* @input : Some key integer.
* @input : Some value,.
* @returns : void. Places (key, value) pairing into map.
* Replaces value if another pairing with this key already exists.
* Do nothing if the table is full!
*/
void put(hash_struct* table, int key, int value){
  int key_hashcode = hashcode(table, key); // starting bucket to try and put
  int i = 0; // for loop counter
  int index; // var to store index and account for wrapping around
  
  if (contains(table, key)) { // Contains a duplicate
    for (i = 0; i < table -> num_of_buckets; i++) {
      index = (key_hashcode + i) % table -> num_of_buckets; // consider wrap around
      if (table -> buckets[index] -> key == key) { // replaceable bucket
        table -> buckets[index] -> key = key;
        table -> buckets[index] -> value = value;
        return; // successfully inserted, can end
      } else {
        continue; // continue through bucket to find open space
      }
    }
  } else {
    // No duplicates, find empty space now
    for (i = 0; i < table -> num_of_buckets; i++) {
      index = (key_hashcode + i) % table -> num_of_buckets; // consider wrap around
      if (table -> buckets[index] -> key == -1) { // empty bucket
        table -> buckets[index] -> key = key;
        table -> buckets[index] -> value = value;
        return; // successfully inserted, can end
      } else {
        continue; // continue through bucket to find open space
      }
    }
  }
  
  // Do nothing if no empty spaces
       
}

/*
* @returns : The number of valid (key, value) pairings in the table.
*/
int size(hash_struct* table){
  int size = 0; // counter for size
  int i = 0; // for loop counter
  
  for (i = 0; i < table -> num_of_buckets; i++) {
    if (table -> buckets[i] -> key != -1 || table -> buckets[i] -> value != -1) {
      size = size + 1; // valid pairings
    } else {
      continue;
    }
  }
  return size;
}

/*
* Iterates through the table and resets all entries.
*/
void clear(hash_struct* table){
  int i = 0; // for loop counter
  
  for (i = 0; i < table -> num_of_buckets; i++) { // Check reset non-empty values
    if (table -> buckets[i] -> key != -1 || table -> buckets[i] -> value != -1) {
      table -> buckets[i] -> key = -1; // set to empty
      table -> buckets[i] -> value = -1; // set to empty
    } else {
      continue;
    }
  }
}

/*
* @returns : true, only if the table contains 0 valid (key, value) pairings.
*/
bool isEmpty(hash_struct* table){
  int i = 0; // for loop counter
  
  for (i = 0; i < table -> num_of_buckets; i++) { // Check valid values
    if (table -> buckets[i] -> key != -1 || table -> buckets[i] -> value != -1) {
      return false;
    } else {
      continue;
    }
  }
  
  return true;
}


/*
* @returns : true, only when the table is filled entirely with VALID values.
*/
bool isFull(hash_struct* table){
  int i = 0; // for loop counter
  
  for (i = 0; i < table -> num_of_buckets; i++) { // Check non-valid values
    if (table -> buckets[i] -> key == -1 && table -> buckets[i] -> value == -1) {
      return false;
    } else {
      continue;
    }
  }
  
  return true;
}


/*
* @input : Some key value.
* @returns : void. if a pair exists for this key, reinitialize this entry.
*/
void removeEntry(hash_struct* table, int key){
  int key_hashcode = hashcode(table, key); // starting bucket to try and put
  int i = 0; // for loop counter
  int index; // var to store index and account for wrapping around
  
  for (i = 0; i < table -> num_of_buckets; i++) {
    index = (key_hashcode + i) % table -> num_of_buckets; // consider wrap around
    if (table -> buckets[index] -> key == key) { // found bucket with key
      table -> buckets[index] -> key = -1;
      table -> buckets[index] -> value = -1;
      return; // successfully reinitialized
    } else {
      continue; // continue through bucket to find correct key
    }
  }
  // No matching key: do nothing
    
}


/*
* Debugging function.
* Iterates through the hashTable and prints all NON-NULL (key, value) pairings.
* Print statement should be of the form "(key1, value1), (key2, value2), ...."
*/
void printEntries(hash_struct* table){
  int i = 0; // for loop counter
  
  for (i = 0; i < table -> num_of_buckets; i++) {
    if (table -> buckets[i] != NULL) {
      printf("(%d, %d), ", table -> buckets[i] -> key, table -> buckets[i] -> value);
    }
  }
  printf("\n");
}

/*
* Debugging function.
* Iterates though the hashTable and prints ALL entries in order.
* If a value is not valid, you will print "EMPTY" for the value.
* Entry print Format: "(INDEX: tableIndex, KEY: key, VALUE: value)"
* Example :  "(INDEX: 0, KEY: 0, VALUE: 3), (INDEX: 1, KEY: EMPTY, VALUE: EMPTY), (INDEX: 2, KEY: 2, VALUE: 49), ..."
*/
void printFullTable(hash_struct* table){
  int i = 0; // for loop counter
  
  for (i = 0; i < table -> num_of_buckets; i++) {
    if (table -> buckets[i] -> value == -1) {
      printf("(INDEX: %d, KEY: EMPTY, VALUE: EMPTY), ", i);
    } else {
      printf("(INDEX: %d, KEY: %d, VALUE: %d), ", i, table -> buckets[i] -> key, table -> buckets[i] -> value);
    }
  }
  
  printf("\n");
      
}


/**
* Should free all space consumed by the hash table.
*/
void done(hash_struct* table){
  int i = 0; // for loop counter
  for (i = 0; i < table -> num_of_buckets; i++) {
    free(table -> buckets[i]); // free each data entry memory
  }
  free(table -> buckets); // free buckets memory
  free(table); // free entire hash_struct memory
        

}