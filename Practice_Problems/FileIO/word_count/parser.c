#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#define MOVE_TO_WORD_BEGIN(t) while(!isalpha(*t) && *t) \
				t++;
#define MOVE_TO_WORD_END(t) while(isalpha(*t)) \
				t++;
#define MARK_WORD_END(t) *t++ = '\0'

static char* ptr;
static char* line_end;
static	unsigned isFirstPass = 1;

static char* MarkWords(char* s){
	while(s < line_end){
		MOVE_TO_WORD_BEGIN(s);
		MOVE_TO_WORD_END(s);
		MARK_WORD_END(s);
	}		
}

char* Parser_GetWords(char* s, size_t len){
	if(!len || *s == '\n') return NULL;
	if(isFirstPass){
		line_end = s + len - 1;
		ptr = s;
		MarkWords(s);
		isFirstPass = 0;
		MOVE_TO_WORD_BEGIN(ptr);
		return *ptr ? ptr : NULL;
	}
	if(ptr < line_end){
		MOVE_TO_WORD_END(ptr);
		ptr++;
		MOVE_TO_WORD_BEGIN(ptr);
	}
	return (ptr < line_end) ? ptr : NULL;
}

void Parser_Reset(void){
	ptr = NULL;
	line_end = NULL;
	isFirstPass = 1;
}
