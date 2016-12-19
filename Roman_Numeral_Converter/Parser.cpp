#include <iostream>
#include <cctype>
#include <cstdlib>
#include "Parser.h"

/* SKIP_WHITE_SPACE: moves past spaces in string s */
#define SKIP_WHITE_SPACE(s) {		\
		while(isspace(*s))	\
			s++;		\
	}

/* MARK_STR_END: marks a word by placing a null character
	at the location of the first space past the word.
	Also makes sure all alpha characters are uppercase. */
#define MARK_STR_END(s) {				\
		while(!isspace(*s) && *s){ 			\
			if(isalpha(*s))			\
				*s = toupper(*s);	\
			s++;	    			\
		}					\
	  	*s = '\0';				\
	}

/* COPY: copies string s into string t */
#define COPY(t, s) {			\
		while(*s)		\
			*t++ = *s++;	\
	}

/* SPACE_OUT: writes spaces to properly align words */
#define SPACE_OUT(t, origStr, n) {			\
		while((unsigned)(t - origStr) < n)	\
			*t++ = ' ';			\
	}

/* Constructor sets the begin and end position of the arab numeral in the string */
Parser::Parser() : ARB_BEG_POS(16), ARB_END_POS(20)
{}

/* Parse: marks the end of the numeral substring in string t and returns a pointer
	to the numeral substring; returns NULL if error */
char* Parser::Parse(char* t){
	char* s = t;

	SKIP_WHITE_SPACE(s);
	t = s;
	MARK_STR_END(s);
	if(*t == '\0')
		return NULL;
	return t;
}

/* Unparse: puts numeral substring supplied by translator into the proper place in the
		output string and returns a pointer to the output string */
char* Parser::Unparse(char* origStr, const char* s){
	char* t = origStr;
	if(isalpha(*s)){
		COPY(t, s);
		SPACE_OUT(t, origStr, ARB_BEG_POS);
	}
	else
		while(*t)
			t++;

	SPACE_OUT(t, origStr, ARB_BEG_POS);

	if(isdigit(*s)){
		COPY(t, s);
		SPACE_OUT(t, origStr, ARB_END_POS);
	}
	else
		while(*t)
			t++;
	SPACE_OUT(t, origStr, ARB_END_POS);

	*t = '\0';
	return origStr;
}

/* Build: Takes as input the roman numeral string s and the arabic numearal string
	t and builds a new string.  Returns a pointer to the new string.
	Returned pointer must be deleted by the calling function. */
char* Parser::Build(const char* s, const char* t){
	char* string = new char[ARB_END_POS + 1]();
	char* p = string;
	COPY(p, s);
	return Unparse(string, t);
}
