// Antoine Rocha
// arocha4
// Cmps12b
// pa5
// Dictionary.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dictionary.h"
const int tableSize = 101;

// Node Object 
typedef struct NodeObj {
 char * Key;
 char * Value;
 struct NodeObj * next;
}
NodeObj;
typedef NodeObj * Node;

// Constructor for Node Type
Node newNode(char * k, char * v) {
 Node H = malloc(sizeof(Node));
 assert(H != NULL);
 H -> Key = k;
 H -> Value = v;
 H -> next = NULL;
 return (H);
}

// Free Node memory 
void freeNode(Node * FN) {
 if (FN != NULL && * FN != NULL) {
  free( * FN); * FN = NULL;
 }
}

// Create data type 
typedef struct DictionaryObj {
 Node * Htable;
 int NumberOfItems;
}
DictionaryObj;

// Constructor for Dictionary Type 
Dictionary newDictionary() {
  Dictionary dictionary = malloc(sizeof(Dictionary));
  assert(dictionary != NULL);
  dictionary -> Htable = calloc(tableSize, sizeof(Node));
  assert(dictionary -> Htable != NULL);
  dictionary -> NumberOfItems = 0;
  return dictionary;
 }
 // rotate_left()
unsigned int rotate_left(unsigned int Value, int Shift) {
 int Bitslength = 8 * sizeof(unsigned int);
 Shift = Shift & (Bitslength - 1);
 if (Shift == 0)
  return Value;
 return (Value << Shift) | (Value >> (Bitslength - Shift));
}


// pre_hash()
unsigned int pre_hash(char * input) {
 unsigned int Result = 0xBAE86554;
 while ( * input) {
  Result ^= * input++;
  Result = rotate_left(Result, 5);
 }
 return Result;
}

// hash()
int hash(char * Key) {
 return pre_hash(Key) % tableSize;
}



//isEmpty()
int isEmpty(Dictionary dictionary) {
 if (dictionary == NULL) {
  fprintf(stderr, "Error:isEmpty() is NULL\n");
  exit(EXIT_FAILURE);
 }
 if (dictionary -> NumberOfItems > 0) {
  return 0;
 }
 return 1;
}

//findKey()
Node findKey(Dictionary dictionary, char * k) {
 Node H;
 H = dictionary -> Htable[hash(k)];
 while (H != NULL) {
  if (strcmp(H -> Key, k) == 0)
   break;
  H = H -> next;
 }
 return H;
}

// lookup()
char * lookup(Dictionary dictionary, char * k) {
 if (dictionary == NULL) {
  fprintf(stderr, "Error: calling lookup() on NULL Dictionary\n");
  exit(EXIT_FAILURE);
 }
 if (dictionary -> NumberOfItems == 0) {
  fprintf(stderr, "Error: calling lookup() on empty Dictionary reference");
  exit(EXIT_FAILURE);
 }
 if (findKey(dictionary, k) == NULL)
  return NULL;
 else
  return findKey(dictionary, k) -> Value;
}

// size()
int size(Dictionary dictionary) {
 return dictionary -> NumberOfItems;
}

// FreeDictionary()
void freeDictionary(Dictionary * FD) {
 if (FD != NULL && * FD != NULL) {
  makeEmpty( * FD);
  free(( * FD) -> Htable);
  free( * FD); * FD = NULL;
 }
}

// insert()
void insert(Dictionary dictionary, char * k, char * v) {
 Node H;
 int j = hash(k);
 if (dictionary == NULL) {
  fprintf(stderr, "Error: insert()  NULL Dictionary\n");
  exit(EXIT_FAILURE);
 }
 if (findKey(dictionary, k) != NULL) {
  fprintf(stderr, "Error: calling insert() on a pre-existing Key");
  exit(EXIT_FAILURE);
 }
 if (dictionary -> Htable[j] == NULL) {
  dictionary -> Htable[j] = newNode(k, v);
  dictionary -> NumberOfItems++;
 } else {
  H = newNode(k, v);
  H -> next = dictionary -> Htable[j];
  dictionary -> Htable[j] = H;
  dictionary -> NumberOfItems++;
 }
}

// delete()
void delete(Dictionary dictionary, char * k) {
  Node H;
  Node I;
  if (findKey(dictionary, k) == NULL) {
   fprintf(stderr, "errror: Key not found\n");
   exit(EXIT_FAILURE);
  }
  H = findKey(dictionary, k);
  if (H == dictionary -> Htable[hash(k)] && H -> next == NULL) {
   H = NULL;
   freeNode( & H);
  } else if (H == dictionary -> Htable[hash(k)]) {
   dictionary -> Htable[hash(k)] = H -> next;
   H = NULL;
   freeNode( & H);
  } else {
   I = dictionary -> Htable[hash(k)];
   while (I -> next != H) {
    I = I -> next;
   }
   I -> next = H -> next;
   freeNode( & H);

  }
  dictionary -> NumberOfItems--;
 }
 // MakeEmpty()
void makeEmpty(Dictionary dictionary) {
  for (int j = 0; j < tableSize; j++) {
   while (dictionary -> Htable[j] != NULL) {
    Node H;
    H = dictionary -> Htable[j];
    dictionary -> Htable[j] = H -> next;
    freeNode( & H);
    H = NULL;
   }
  }
  dictionary -> NumberOfItems = 0;

 }
 // printDictionary()
void printDictionary(FILE * out, Dictionary dictionary) {
 Node H;
 if (dictionary == NULL) {
  fprintf(stderr, "Error: printDictionary() NULL Dictionary/n");
  exit(EXIT_FAILURE);
 }
 for (int j = 0; j < tableSize; j++) {
  H = dictionary -> Htable[j];
  while (H != NULL) {
   fprintf(out, "%s %s \n", H -> Key, H -> Value);
   H = H -> next;
  }
 }

}