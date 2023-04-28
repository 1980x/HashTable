#ifndef _LIST_H__
#define _LIST_H__
#define MAX_STR_LEN 25
#define LIST_EMPTY  10
#define NOT_FOUND   20
#define ELEMENT_FOUND 30
#define ELEMENT_NOT_FOUND 40
#define NOT_IMPLEMENTED 50

//Declaring struct Node
struct Node {
  struct Node *next;
  char word[MAX_STR_LEN];
};

//typedef for Node and NodePtr
typedef struct Node Node;
typedef struct Node* NodePtr;

struct List {
  NodePtr head;
  unsigned int size;
};

typedef struct List List;
typedef struct List* ListPtr;

ListPtr CreateList();
ListPtr* CreateArrayOfListPtrs(unsigned size);
void List_Prepend(ListPtr list,char *word) ;
NodePtr CreateNewNode(char *word);
void PrintList(ListPtr list) ;
int List_Delete(ListPtr list, char *word, int *pos) ;
int List_Position(ListPtr list, char *word, int *pos) ;
#endif
