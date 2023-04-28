#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hash.h"

#define MAX_ARGUMENTS 3
#define MAX_STR_LEN 25 //Maximum length of each word
#define TRUE 1
#define FALSE 0

#define STOP_GRADING fprintf(stderr," Stopping grading . Please PASS THIS TEST CASE BEFORE CONTINUING");\
     		     exit(EXIT_FAILURE);

#define INC_MARKS(M) if(pass){\
                      total_marks += M;\
		     }
#define WORD_MATCH(A,B) (strcmp(A,B) == 0)
#define PRINTRESULT (pass?"PASS":"FAIL"),(pass?subtest_marks:0)
void Test_CreateNewNode(int testNum, char *name, int *marks);
void Test_CreateList(int testNum, char *name, int *marks );
void Test_ListPrepend(int testNum, char *name, int *marks ) ;
void Test_ListPosition(int testNum, char *name, int *marks ) ;
void Test_ListDelete(int testNum, char *name, int *marks ) ;
void assert_func(void *ptr ,char *msg) ;
void StopGrading(char *msg);

#define CHECK_NULL(ptr,msg) assert_func(ptr,msg);
int total_marks = 0;



int main(int argc, char **argv) {
  
  //Check if the program has two arguments
  if(argc != MAX_ARGUMENTS) {
    fprintf(stderr,"Insufficient arguments\n");
    fprintf(stderr,"./dictionary <filename> <tablesize>");
    exit(EXIT_FAILURE);
  }

  //Open file for reading 
  FILE *fp = fopen(argv[1],"r");
  if(fp == NULL) {
    fprintf(stderr,"Could not open file %s\n",argv[1]);
    exit(EXIT_FAILURE);
  }

  /*** CHECKING LIST ***/
  int test_marks = 0;
  fprintf(stderr,"/**** CHECKING LIST API ****/\n");

  Test_CreateNewNode(1,"CreateNewNode" , &test_marks );
  //total_marks += test_marks;

  test_marks = 0;
  Test_CreateList(2,"CreateList" , &test_marks );
  //total_marks += test_marks;

  test_marks = 0;
  Test_ListPrepend(3,"List_Prepend" , &test_marks );
  //total_marks += test_marks;

  test_marks = 0;
  Test_ListPosition(4,"List_Position" , &test_marks );
  //total_marks += test_marks;

  test_marks = 0;
  Test_ListDelete(5,"List_Delete" , &test_marks );
  //total_marks += test_marks;

  printf("\n********* PASSED *********\n");
  printf("Total Marks = %3d\n",total_marks);

  //unsigned tableSize = atoi(argv[2]);
  //fprintf(stderr,"Creating hashtable of size %d using %s\n",tableSize,argv[1]);

  /*
  //Create Hash table
  HashTablePtr htablePtr = CreateHashTable(tableSize);

  char word[MAX_STR_LEN];
  while(fscanf(fp,"%s",word) > 0) {
    AddWordToHashTable(htablePtr,word);
  }
  //Created Hash Table and Printing the hash table
  PrintHashTable(htablePtr);
  */
}

void Test_CreateNewNode(int testNum, char *name, int *marks ) {
  int pass = FALSE;
  int subtest_marks = 1;
  fprintf(stderr,"TEST %2d: %s\n",testNum,name);

  NodePtr node = CreateNewNode("test");
  CHECK_NULL(node,"CreateNewNode cannot return NULL.");

  if(node->next == NULL ) {
    pass = TRUE;
    fprintf(stderr,"TEST %da: Check next ptr initialized to NULL: %s(%dM)\n",testNum,PRINTRESULT);
    INC_MARKS(subtest_marks);
  }else {
    free(node);
    StopGrading("Implement CreateNewNode correctly. Next ptr must be set to NULL");
  }
  
  pass = FALSE;
  if(WORD_MATCH(node->word,"test")) {
    pass = TRUE;
    INC_MARKS(1);
    fprintf(stderr,"TEST %da: Check if word copied: %s(%dM)\n",testNum,PRINTRESULT);
  }else {
    fprintf(stderr,"TEST %da: Word not copied. Word is %s: %s(%dM)\n",testNum,node->word,PRINTRESULT);
    free(node);
    StopGrading("Implement CreateNewNode correctly. Please use strcpy to copy the word");
  }
}

void Test_CreateList(int testNum, char *name, int *marks ) {
  int pass = FALSE;
  int subtest_marks = 1;
  fprintf(stderr,"TEST %2d: %s\n",testNum,name);

  ListPtr listPtr = CreateList();
  CHECK_NULL(listPtr,"CreateList cannot return NULL.");

  if(listPtr->head == NULL ) {
    pass = TRUE;
    fprintf(stderr,"TEST %da: Check head ptr initialized to NULL: %s(%dM)\n",testNum,PRINTRESULT);
    INC_MARKS(subtest_marks);
  }else{
    free(listPtr);
    pass = FALSE;
    fprintf(stderr,"TEST %da: list->head ptr must be initialized to NULL: %s(%dM)\n",testNum,PRINTRESULT);
    StopGrading("Implement CreateList correctly. Please set list->head to NULL");
  }
  
  
  if(listPtr->size == 0) {
    pass = TRUE;
    fprintf(stderr,"TEST %da: Check if list size is 0: %s(%dM)\n",testNum,PRINTRESULT);
    INC_MARKS(subtest_marks);
  }else{
    free(listPtr);
    pass = FALSE;
    fprintf(stderr,"TEST %da: list->size must be 0 . list->size =%d : %s(%dM)\n",testNum,listPtr->size,PRINTRESULT);
    StopGrading("Implement CreateList correctly. Please set list->size to 0");
  }

}

void Test_ListPrepend(int testNum, char *name, int *marks ) {
  int pass = FALSE;
  int subtest_marks = 1;
  fprintf(stderr,"TEST %2d: %s\n",testNum,name);

  ListPtr listPtr = CreateList();

  List_Prepend(listPtr,"Sai");

  if(listPtr->head != NULL ) {

    if(WORD_MATCH(listPtr->head->word,"Sai") ){
      pass = TRUE;
      fprintf(stderr,"TEST %da: First node initialized with word \"Sai\": %s(%dM)\n",testNum,PRINTRESULT);
      INC_MARKS(subtest_marks);
    }else {
      pass = FALSE;
      fprintf(stderr,"TEST %da: First node not initialized with word \"Sai\": %s(%dM)\n",testNum,PRINTRESULT);
      StopGrading("Implement List_Prepend correctly. Please use strcpy to copy the word");
    }

    if(listPtr->size == 1 ){
      pass = TRUE;
      fprintf(stderr,"TEST %db: List size is 1 : %s(%dM)\n",testNum,PRINTRESULT);
      INC_MARKS(1);
    }else {
      pass = FALSE;
      fprintf(stderr,"TEST %db: List size is wrong after prepend. List size is %d: %s(%dM)\n",testNum,listPtr->size,
                                                                         PRINTRESULT);
      StopGrading("Implement List_Prepend correctly. Please increment after appending");
    }

    List_Prepend(listPtr,"Ram");
    List_Prepend(listPtr,"Sathya");
    if(WORD_MATCH(listPtr->head->word,"Sathya") ){
      pass = TRUE;
      fprintf(stderr,"TEST %dc: Prepend Ram followed by Sathya: %s(%dM)\n",testNum,PRINTRESULT);
      INC_MARKS(1);
    }else {
      pass = FALSE;
      fprintf(stderr,"TEST %dc: Prepend Ram followed by Sathya: %s(%dM)\n",testNum,PRINTRESULT);
    }

    if(listPtr->size == 3 ){
      pass = TRUE;
      fprintf(stderr,"TEST %dd: List size is 3 : %s(%dM)\n",testNum,PRINTRESULT);
      INC_MARKS(1);
    }else {
      pass = FALSE;
      fprintf(stderr,"TEST %dd: List size is wrong after prepend. List size is %d: %s(%dM)\n",testNum,listPtr->size,
                                                                         PRINTRESULT);
    }


  }else{
    StopGrading("List_Prepend. Newnode not allocated or list->head is NULL");
    free(listPtr);
  }
  
  free(listPtr);
}

void Test_ListPosition(int testNum, char *name, int *marks ) {
  int pass = FALSE;
  int subtest_marks = 1;
  fprintf(stderr,"TEST %2d: %s\n",testNum,name);

  ListPtr listPtr = CreateList();

  List_Prepend(listPtr,"Ram");
  List_Prepend(listPtr,"Sai");
  List_Prepend(listPtr,"Sathya");

   int pos ;

   int returnType = List_Position(listPtr, "Ram", &pos);
   if(returnType == ELEMENT_FOUND && pos == 2) {
      pass = TRUE;
      INC_MARKS(1);
      fprintf(stderr,"TEST %da: Linked List [Sathya->Sai->Ram]. Searching for Ram returned ELEMENT_FOUND and pos=2: %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
   }else {
      pass = FALSE;
      if(returnType == ELEMENT_NOT_FOUND ) {
         fprintf(stderr,"TEST %da: Linked List [Sathya->Sai->Ram]. Searching for Ram returned ELEMENT_NOT_FOUND : %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
      }else if(pos != 2 ) {
         fprintf(stderr,"TEST %da: Linked List [Sathya->Sai->Ram]. Searching for Ram returned pos=%d : %s(%dM)\n",                                                                                          testNum,pos,PRINTRESULT);
      }
   }

   returnType = List_Position(listPtr, "Sathya", &pos);
   if(returnType == ELEMENT_FOUND && pos == 0) {
      pass = TRUE;
      INC_MARKS(1);
      fprintf(stderr,"TEST %db: Linked List [Sathya->Sai->Ram]. Searching for Sathya returned ELEMENT_FOUND and pos=0: %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
   }else {
      pass = FALSE;
      if(returnType == ELEMENT_NOT_FOUND ) {
         fprintf(stderr,"TEST %db: Linked List [Sathya->Sai->Ram]. Searching for Sathya returned ELEMENT_NOT_FOUND : %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
      }else if(pos != 0 ) {
         fprintf(stderr,"TEST %db: Linked List [Sathya->Sai->Ram]. Searching for Sathya returned pos=%d : %s(%dM)\n",                                                                                          testNum,pos,PRINTRESULT);
      }
   }

   returnType = List_Position(listPtr, "Sai", &pos);
   if(returnType == ELEMENT_FOUND && pos == 1) {
      pass = TRUE;
      INC_MARKS(1);
      fprintf(stderr,"TEST %db: Linked List [Sathya->Sai->Ram]. Searching for Sai returned ELEMENT_FOUND and pos=1: %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
   }else {
      pass = FALSE;
      if(returnType == ELEMENT_NOT_FOUND ) {
         fprintf(stderr,"TEST %db: Linked List [Sathya->Sai->Ram]. Searching for Sai returned ELEMENT_NOT_FOUND : %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
      }else if(pos != 1 ) {
         fprintf(stderr,"TEST %db: Linked List [Sathya->Sai->Ram]. Searching for Sai returned pos=%d : %s(%dM)\n",                                                                                          testNum,pos,PRINTRESULT);
      }
   }

   returnType = List_Position(listPtr, "Apple", &pos);
   if(returnType == ELEMENT_NOT_FOUND && pos == -1) {
      pass = TRUE;
      INC_MARKS(1);
      fprintf(stderr,"TEST %dc: Linked List [Sathya->Sai->Ram]. Searching for Apple returned ELEMENT_NOT_FOUND and pos=-1: %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
   }else {
      pass = FALSE;
      if(returnType == ELEMENT_FOUND ) {
         fprintf(stderr,"TEST %dc: Linked List [Sathya->Sai->Ram]. Searching for Apple returned ELEMENT_FOUND : %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
      }else if(pos != -1 ) {
         fprintf(stderr,"TEST %dc: Linked List [Sathya->Sai->Ram]. Searching for Apple returned pos=%d : %s(%dM)\n",                                                                                          testNum,pos,PRINTRESULT);
      }
   }


  free(listPtr);
}

void Test_ListDelete(int testNum, char *name, int *marks ) {
  int pass = FALSE;
  int subtest_marks = 1;
  int pos ;
  fprintf(stderr,"TEST %2d: %s\n",testNum,name);

  ListPtr listPtr = CreateList();



   int returnType = List_Delete(listPtr, "Apple", &pos);
   if(returnType == LIST_EMPTY && pos == -1) {
      pass = TRUE;
      INC_MARKS(subtest_marks);
      fprintf(stderr,"TEST %da: Linked List empty []. Deleting Apple returned LIST_EMPTY and pos=-1: %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
      if(listPtr->size == 0) {
        pass = TRUE;
        INC_MARKS(subtest_marks);
        fprintf(stderr,"TEST %da: Linked List empty []. Deleting Apple. List size is 0 unmodified: %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
      }else {
        pass = FALSE;
        fprintf(stderr,"TEST %da: Linked List [Sathya->Sai->Ram]. Deleting Apple. List size is %d: %s(%dM)\n",                                                                                          testNum,listPtr->size,PRINTRESULT);
      }

   }else {
      pass = FALSE;
      if(returnType != LIST_EMPTY ) {
         fprintf(stderr,"TEST %da: Linked List [Sathya->Sai->Ram]. Deleting Apple returned %d : %s(%dM)\n",                                                                                          testNum,returnType,PRINTRESULT);
      }else if(pos != -1 ) {
         fprintf(stderr,"TEST %da: Linked List [Sathya->Sai->Ram]. Deleting Apple returned pos=%d : %s(%dM)\n",                                                                                          testNum,pos,PRINTRESULT);
      }
   }

   List_Prepend(listPtr,"Ram");
   List_Prepend(listPtr,"Sai");
   List_Prepend(listPtr,"Sathya");

   returnType = List_Delete(listPtr, "Apple", &pos);
   if(returnType == ELEMENT_NOT_FOUND && pos == -1) {
      pass = TRUE;
      INC_MARKS(subtest_marks);
      fprintf(stderr,"TEST %db: Linked List [Sathya->Sai->Ram]. Deleting Apple returned ELEMENT_NOT_FOUND and pos=-1: %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
      if(listPtr->size == 3) {
        pass = TRUE;
        INC_MARKS(subtest_marks);
        fprintf(stderr,"TEST %db: Linked List [Sathya->Sai->Ram]. Deleting Apple. List size is 3 unmodified: %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
      }else {
        fprintf(stderr,"TEST %db: Linked List [Sathya->Sai->Ram]. Deleting Apple. List size is %d: %s(%dM)\n",                                                                                          testNum,listPtr->size,PRINTRESULT);
      }

   }else {
      pass = FALSE;
      if(returnType != ELEMENT_NOT_FOUND ) {
         fprintf(stderr,"TEST %db: Linked List [Sathya->Sai->Ram]. Deleting Apple returned %d : %s(%dM)\n",                                                                                          testNum,returnType,PRINTRESULT);
      }else if(pos != -1 ) {
         fprintf(stderr,"TEST %db: Linked List [Sathya->Sai->Ram]. Deleting Apple returned pos=%d : %s(%dM)\n",                                                                                          testNum,pos,PRINTRESULT);
      }
   }

   returnType = List_Delete(listPtr, "Sai", &pos);
   if(returnType == ELEMENT_FOUND && pos == 1) {
      pass = TRUE;
      INC_MARKS(subtest_marks);
      fprintf(stderr,"TEST %dc: Linked List [Sathya->Sai->Ram]. Deleting Sai returned ELEMENT_FOUND and pos=1: %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
      if(listPtr->size == 2) {
        pass = TRUE;
        INC_MARKS(subtest_marks);
        fprintf(stderr,"TEST %dc: Linked List [Sathya->Sai->Ram]. Deleting Sai. List size is 2: %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
      }else {
        fprintf(stderr,"TEST %dc: Linked List [Sathya->Sai->Ram]. Deleting Sai. List size is %d: %s(%dM)\n",                                                                                          testNum,listPtr->size,PRINTRESULT);
      }

   }else {
      pass = FALSE;
      if(returnType == ELEMENT_NOT_FOUND ) {
         fprintf(stderr,"TEST %dc: Linked List [Sathya->Sai->Ram]. Deleting Sai returned ELEMENT_NOT_FOUND : %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
      }else if(pos != 1 ) {
         fprintf(stderr,"TEST %dc: Linked List [Sathya->Sai->Ram]. Deleting Sai returned pos=%d : %s(%dM)\n",                                                                                          testNum,pos,PRINTRESULT);
      }
   }

   returnType = List_Delete(listPtr, "Ram", &pos);
   if(returnType == ELEMENT_FOUND && pos == 1) {
      pass = TRUE;
      INC_MARKS(subtest_marks);
      fprintf(stderr,"TEST %dd: Linked List [Sathya->Ram]. Deleting Ram returned ELEMENT_FOUND and pos=1: %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
      if(listPtr->size == 1) {
        pass = TRUE;
        INC_MARKS(subtest_marks);
        fprintf(stderr,"TEST %dd: Linked List [Sathya->Ram]. Deleting Ram. List size is 1: %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
      }else {
        pass = FALSE;
        fprintf(stderr,"TEST %dd: Linked List [Sathya->Ram]. Deleting Ram. List size is %d: %s(%dM)\n",                                                                                          testNum,listPtr->size,PRINTRESULT);
      }

   }else {
      pass = FALSE;
      if(returnType == ELEMENT_NOT_FOUND ) {
         fprintf(stderr,"TEST %dd: Linked List [Sathya->Ram]. Deleting Ram returned ELEMENT_NOT_FOUND : %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
      }else if(pos != 2 ) {
         fprintf(stderr,"TEST %dd: Linked List [Sathya->Ram]. Deleting Ram returned pos=%d : %s(%dM)\n",                                                                                          testNum,pos,PRINTRESULT);
      }
   }

   returnType = List_Delete(listPtr, "Sathya", &pos);
   if(returnType == ELEMENT_FOUND && pos == 0) {
      pass = TRUE;
      INC_MARKS(subtest_marks);
      fprintf(stderr,"TEST %de: Linked List [Sathya->Ram]. Deleting Sathya returned ELEMENT_FOUND and pos=0: %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
      if(listPtr->size == 0) {
        pass = TRUE;
        INC_MARKS(subtest_marks);
        fprintf(stderr,"TEST %de: Linked List [Sathya->Ram]. Deleting Sathya. List size is 0: %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
      }else {
        pass = FALSE;
        fprintf(stderr,"TEST %de: Linked List [Sathya->Ram]. Deleting Sathya. List size is %d: %s(%dM)\n",                                                                                          testNum,listPtr->size,PRINTRESULT);
      }
      if(listPtr->head == 0) {
        pass = TRUE;
        INC_MARKS(subtest_marks);
        fprintf(stderr,"TEST %de: Linked List [Sathya->Ram]. Deleting Sathya. List head is set to NULL: %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
      }else {
        pass = FALSE;
        fprintf(stderr,"TEST %de: Linked List [Sathya->Ram]. Deleting Sathya. List head is %p: %s(%dM)\n",                                                                                          testNum,listPtr->head,PRINTRESULT);
      }

   }else {
      pass = FALSE;
      if(returnType == ELEMENT_NOT_FOUND ) {
         fprintf(stderr,"TEST %de: Linked List [Sathya->Ram]. Deleting Sathya returned ELEMENT_NOT_FOUND : %s(%dM)\n",                                                                                          testNum,PRINTRESULT);
      }else if(pos != 2 ) {
         fprintf(stderr,"TEST %de: Linked List [Sathya->Ram]. Deleting Sathya returned pos=%d : %s(%dM)\n",                                                                                          testNum,pos,PRINTRESULT);
      }
   }


  free(listPtr);
}

void assert_func(void *ptr ,char *msg) {
  if(ptr == NULL) {
    StopGrading(msg);
  }
}

void StopGrading(char *msg){
  fprintf(stderr,"\n\n************ERROR**************************\n");
  fprintf(stderr,"%s\n",msg);
  fprintf(stderr,"Total Marks : %d\n ",total_marks);
  fprintf(stderr,"**********EXITING GRADING*************\n\n\n");
  exit(EXIT_FAILURE);

}
