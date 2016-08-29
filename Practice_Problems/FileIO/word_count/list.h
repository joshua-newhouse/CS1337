#ifndef LIST_H
#define LIST_H
#include "item.h"

typedef struct node node_ts;
struct node{
	item_ts item;
	node_ts* nextNode;
};

int List_AddEntry(const char*);
void List_Traverse(void (*func)(item_ts*));
void List_Delete(void);

#endif
