// Antoine Rocha
// arocha4
// Cmps12b
// pa5
// test for dictionary ADT
// DictionaryTest.c


#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h"

int main(int argc, char* argv[]){
    Dictionary D = newDictionary();
    FILE* out = fopen("DictionaryTest_out", "w");
    char* key = "Hello";
    char* val = "sir";
    char* key2 = "how";
    char* val2 = "are";
    char* key3 = "you";
    char* val3 = "faring";
	char* key4 = "on this";
    char* val4 = "day";
    insert(D, key, val);
    insert(D, key2, val2);
    insert(D, key3, val3);
    delete(D, key);
    printDictionary(out, D);
	delete(D, key2);
	printDictionary(out, D);
	makeEmpty(D);
	printDictionary(D,stdout);
	}

