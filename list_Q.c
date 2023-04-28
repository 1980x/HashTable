#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"list.h"

/*All functions in this file need to be implemented by you except PrintList*/

//Checkpoints
//DEF: Create a new node, store the word and return the address
//1. Check if malloc returned NULL
NodePtr CreateNewNode(char *word){
  return NULL;
}

//Checkpoints
//DEF: Create a List and return ListPtr
//1. Check if malloc returned NULL
//2. Initialize the head and size appropriately
ListPtr CreateList() {
  return NULL;
}

//Checkpoints:
//DEF: Create an array of  List pointers and return them
//1. size=0. return NULL
//2. Call CreateList() while creating the lists
//3. Check if malloc returned NULL
// Please always check if malloc returned NULL and assert 

ListPtr* CreateArrayOfListPtrs(unsigned size) {
   return NULL;
}

//
//DEF: Add word to the beginning of the list
//Checkpoints
//1. strcpy would be necessary to store the words
void List_Prepend(ListPtr list,char *word) {
  if(list == NULL) {
   fprintf(stderr,"Empty List passed \n");
   exit(EXIT_FAILURE);
  }
}


//DEF Delete first occurence of the element from the list 
//Checkpoints 
//1. Set pos to the position where the word was found in the list 
//2. Set pos to -1 if the element was not found or the list is empty
//3. Return type 
// a. LIST_EMPTY     ==> If the list is empty 
// b. ELEMENT_FOUND  ==> If the word was found in the list and also set pos which is a pointer variable
// c. NOT FOUND      ==> If the word was not found in the list 
// Free the node 
int List_Delete(ListPtr list, char *word, int *pos) {
   return NOT_IMPLEMENTED;
}

//DEF: This function is List Find 
//Checkpoints :
//Set pos = -1 and ELEMENT_NOT_FOUND if element not found or list is empty
//Return ELEMENT_FOUND if element is found
int List_Position(ListPtr list, char *word, int *pos) {
  return NOT_IMPLEMENTED;
}

//DO NOT MODIFY THIS CODE
//DEF:Print the list
void PrintList(ListPtr list) {

  if(list == NULL) {
   fprintf(stderr,"Empty List passed \n");
   exit(EXIT_FAILURE);
  }

  if(list->size > 0 ) {
    NodePtr temp = list->head;
    for(unsigned i = 0; i < list->size; i++){
      printf("%s",temp->word);
      temp = temp->next;
      if(i != (list->size-1)) {
        printf("->");
      }
    }
    printf("->NULL");
  }else {
    printf("EMPTY");
  }

}
