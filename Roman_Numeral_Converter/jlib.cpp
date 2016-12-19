/* jlib.cpp -- Direct copy of jlib.c
   Josh's library of useful functions */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

namespace jlib{

/* rank:  returns number of digits in the input integer */
unsigned rank(int i){
	unsigned digits = 0;
	while(i){
		digits++;
		i /= 10;
	}
	return digits;
}

/* LeadDigit:  returns the highest ranking digit of an integer */
int LeadDigit(int n){
	int ret_val;
	do
		ret_val = n % 10;
	while((n /= 10) > 0);
	return ret_val;
}

/* Reverse:  reverses string s */
void Reverse(char s[]){
	int c, i, j;

	for(i = 0, j = strlen(s) - 1; i < j; i++, j--){
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/* ItoB:  converts base b (where 2 <= b <= 16) integer n to a string s */
char* ItoB(long n, char s[], int b){

	if(n > INT_MAX || n < INT_MIN){
		printf("Number %ld is outside the integer range of this machine. (%d to %d)\n", n, INT_MIN, INT_MAX);
		s[0] = '\0';
		exit(EXIT_FAILURE);
	}
	if(b < 2 || b > 16){
		printf("Base (%d) must be greater than or equal to 2 and less than or equal to 16.\n", b);
		s[0] = '\0';
		exit(EXIT_FAILURE);
	}

	int i = 0, sign = 1, a;

	if(n < 0)
		sign = -1;
	do{
		a = sign * (n % b);
		if(a > 9)
			s[i++] = a - 10 + 'A';
		else
			s[i++] = a + '0';
	}while(n /= b);
	if(sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	Reverse(s);

	return s;
}

}
