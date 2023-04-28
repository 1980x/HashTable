//DO NOT MODIFY THIS CODE
//PLEASE ONLY IMPLEMENT THE LINKED LIST FUNCTIONS
#include "hash.h"
#include<string.h>
#define SUCCESS  1
#define FAILURE -1

HashTablePtr CreateHashTable(unsigned size){
  HashTablePtr htablePtr = (HashTablePtr) malloc(sizeof(HashTable));
  htablePtr->table =CreateArrayOfListPtrs(size);
  htablePtr->tableSize = size;
  return htablePtr;
}

unsigned HashFunction(char *word, unsigned size){

  unsigned sum = 0;

  if(word == NULL) {
   fprintf(stderr,"word is null\n");
   exit(EXIT_FAILURE);
  }

  if(size <= 0 ) {
   fprintf(stderr,"size is invalid %u\n",size);
   exit(EXIT_FAILURE);
  }

  for(int i =0; i < strlen(word); i++) {
    sum += word[i];  
  }

  return sum % size; 
}

void AddWordToHashTable(HashTablePtr htablePtr,char *word){
   unsigned hashVal = HashFunction(word,htablePtr->tableSize);
   if(hashVal >= 0 && hashVal < htablePtr->tableSize) {
     ListPtr listPtr = htablePtr->table[hashVal];
     List_Prepend(listPtr,word);
   }else{
     fprintf(stderr,"Invalid hashVal %u\n",hashVal);
     exit(EXIT_FAILURE);
   }
}

int  DeleteWordFromHashTable(HashTablePtr htablePtr,char *word){
   unsigned hashVal = HashFunction(word,htablePtr->tableSize);
   int pos ;
   if(hashVal >= 0 && hashVal < htablePtr->tableSize) {
     ListPtr listPtr = htablePtr->table[hashVal];
     List_Delete(listPtr,word,&pos);
   }else{
     fprintf(stderr,"Invalid hashVal %u\n",hashVal);
     exit(EXIT_FAILURE);
   }
 return SUCCESS;
}

void PrintHashTable(HashTablePtr htablePtr){
  if(htablePtr->tableSize > 0 ) {
   printf("****** HASHTABLE ******\n");
   for(unsigned i =0; i < htablePtr->tableSize; i++) {
     printf("L%d: ",i);
     PrintList(htablePtr->table[i]);
     printf("\n");
   }
  }else {
   printf("HASHTABLE EMPTY");
  }
}



