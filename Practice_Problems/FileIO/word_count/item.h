#ifndef ITEM_H
#define ITEM_H

typedef struct{
	char* key;
	unsigned chars;
	unsigned nOccur;
} item_ts;

void Item_ItemTotals(void);
int Item_Increment(item_ts*);
int Item_New(item_ts*, const char*);
void Item_Delete(item_ts*);
void Item_Display(item_ts*);

#endif
