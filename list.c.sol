#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"list.h"

NodePtr CreateNewNode(char *word){
  NodePtr newNode = (NodePtr) malloc(sizeof(Node));
  newNode->next = NULL;
  strcpy(newNode->word,word);
  return newNode;
}

//Checkpoints
//DEF: Create a List and return ListPtr
//1. Check if malloc returned NULL
//2. Initialize the head and size appropriately
ListPtr CreateList() {
  ListPtr listPtr = (ListPtr) malloc(sizeof(List));
  if(listPtr == NULL) {
   fprintf(stderr,"Could not allocate memory");
   exit(EXIT_FAILURE);
  }
  listPtr->head = NULL;
  listPtr->size = 0;
  return listPtr;
}

//Checkpoints:
//DEF: Create an array of  List pointers and return them
//1. size=0. return NULL
//2. Call CreateList() while creating the lists
//3. Check if malloc returned NULL

ListPtr* CreateArrayOfListPtrs(unsigned size) {
   ListPtr *listPtrs = (ListPtr*) malloc(sizeof(ListPtr) * size);

   if(listPtrs == NULL) {
     fprintf(stderr,"Cant allocate memory");
     exit(EXIT_FAILURE);
   }

   for(unsigned int i = 0; i < size; i++) {
     listPtrs[i] = CreateList();
   }
   return listPtrs;
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

  NodePtr newNode = CreateNewNode(word);
  if(newNode == NULL) {
     fprintf(stderr,"Cant allocate memory");
     exit(EXIT_FAILURE);
  }

  newNode->next = list->head;
  list->head = newNode;
  list->size++;
}

//
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
  *pos = -1;
  if(list == NULL) {
    fprintf(stderr,"List cannot be NULL\n");
    exit(EXIT_FAILURE);
  }

  if(list->size > 0 ) {
   NodePtr temp = list->head ;
   if(strcmp(temp->word,word) == 0 ) {

    //Element found at head of the list 
    if(list->size == 1) {
      free(list->head);
      list->size = 0;
      list->head = NULL;
    }else {
      list->head = list->head->next;
      free(temp);
      list->size--;
    }
    *pos = 0;
    return ELEMENT_FOUND;

   }else {

    int position = 1;
    while( (temp->next != NULL)   ) {
      if (strcmp(temp->next->word,word) == 0) {
         //Word found 
	 NodePtr node = temp->next;
	 temp->next = temp->next->next;
	 list->size--;
	 free(node);
	 *pos = position;
	 return ELEMENT_FOUND;
      }
      temp = temp->next;
      position++;
    }

    *pos = -1;
    return ELEMENT_NOT_FOUND;


   }
  }
   return LIST_EMPTY;
}

int List_Position(ListPtr list, char *word, int *pos) {
  NodePtr temp = list->head;
  *pos = 0;
  while(temp != NULL ) {
    if(strcmp(temp->word,word) == 0) {
      return ELEMENT_FOUND;
    }
    (*pos)++;
    temp = temp->next;
  }
  *pos = -1;
  return ELEMENT_NOT_FOUND;
}
