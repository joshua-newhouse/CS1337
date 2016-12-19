#ifndef JLIB_H
#define JLIB_H

namespace jlib{

unsigned rank(int);
int LeadDigit(int);
void Reverse(char []);
char* ItoB(long, char [], int);

}

#endif

/* Useful C functions
	rank returns the number of digits that make up the input integer
	LeadDigit returns the highest ranking digit of an int
	Reverse reverses a string
	ItoB converts an int of base 2 to 16 to a string
*/
