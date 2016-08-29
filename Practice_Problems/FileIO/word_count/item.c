#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

extern FILE* fout;

unsigned tWords, tUniqueWords;

void Item_Display(item_ts* iptr){
	fprintf(fout, "%s %u\n", iptr->key, iptr->chars);
}

void Item_ItemTotals(void){
	fprintf(fout, "Unique Words: %u\nTotal Words: %u\n",
		tUniqueWords, tWords);
}

int Item_Increment(item_ts* iptr){
	iptr->nOccur++;
	tWords++;
	return iptr->nOccur;
}

int Item_New(item_ts* iptr, const char* s){
	iptr->key = (char*)malloc(strlen(s) + 1);
	if(iptr->key == NULL)
		return 0;
	strcpy(iptr->key, s);
	iptr->chars = strlen(iptr->key);
	iptr->nOccur++;
	tUniqueWords++;
	tWords++;
	return 1;
}

void Item_Delete(item_ts* iptr){
	free(iptr->key);
}
