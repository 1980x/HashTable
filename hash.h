#ifndef __HASH_H__
#define __HASH_H__

#include<stdio.h>
#include<stdlib.h>
#include"list.h"

struct HashTable{
 ListPtr *table;
 unsigned tableSize;
};

typedef struct HashTable  HashTable;
typedef struct HashTable* HashTablePtr;

HashTablePtr CreateHashTable(unsigned size);
unsigned HashFunction(char *word, unsigned size);
void AddWordToHashTable(HashTablePtr htablePtr,char *word);
int  DeleteWordFromHashTable(HashTablePtr htabelPtr,char *word);
void PrintHashTable(HashTablePtr htablePtr);
#endif

