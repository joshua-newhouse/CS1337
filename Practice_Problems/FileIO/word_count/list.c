#include <string.h>
#include <stdlib.h>
#include "list.h"
#define MAX_LIST 100

static node_ts* list[MAX_LIST] = {NULL};

static unsigned hash(const char*);
static void DeleteNode(node_ts*);
static node_ts* add(const char*);

static unsigned hash(const char* s){
	unsigned ret_val = 0;
	while(*s)
		ret_val += *s++;
	return ret_val % MAX_LIST;
}

int List_AddEntry(const char* s){
	unsigned h = hash(s);
	if(list[h] == NULL)
		return (list[h] = add(s)) ? 1 : 0;

	node_ts* nptr = list[h];	
	while(strcmp(nptr->item.key, s) && nptr->nextNode)
		nptr = nptr->nextNode;
	if(!strcmp(nptr->item.key, s))
		return Item_Increment(&nptr->item);
	else
		return (nptr->nextNode = add(s)) ? 1 : 0;
}

static node_ts* add(const char* s){
	node_ts* nptr = (node_ts*)malloc(sizeof(node_ts));
	int i;
	if(nptr){
		nptr->nextNode = NULL;
		if(Item_New(&nptr->item, s) == 0)
			return NULL;
	}
	return nptr;
}

void List_Traverse(void (*func)(item_ts* iptr)){
	int i;
	for(i = 0; i < MAX_LIST; i++){
		node_ts* nptr = list[i];
		while(nptr){
			(*func)(&nptr->item);
			nptr = nptr->nextNode;
		}
	}
}

void List_Delete(void){
	List_Traverse(Item_Delete);
	int i;
	for(i = 0; i < MAX_LIST; i++){
		node_ts* nptr = list[i];
		while(nptr){
			node_ts* temp = nptr;
			nptr = nptr->nextNode;
			free(temp);			
		}
	}
}
