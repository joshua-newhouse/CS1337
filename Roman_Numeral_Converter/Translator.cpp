#include <iostream>
#include <cstdlib>
#include "Translator.h"
#include "jlib.h"

/* Constructor allocates array of available roman numeral symbols and displays to stdout */
Translator::Translator() :
	array{
		{'M', 1000},
		{'D',  500},
		{'C',  100},
		{'L',   50},
		{'X',   10},
		{'V',    5},
		{'I',    1},
	}
{
	DisplaySym();
}

/* DisplaySym: Displays available roman numeral symbols and corresponding value */
void Translator::DisplaySym(){
	std::cout << "Available Roman Numerals:" << std::endl;
	for(unsigned i = 0; i < ROM_NUM_SYM; i++)
		std::cout << array[i].symbol << " "
			  << array[i].value << std::endl;
}

/* peek: Returns true if next roman numeral symbol is greater than preceding symbol
	ex: CD; returns false otherwise */
bool Translator::peek(char next, int cur_pos){
	while(--cur_pos >= 0)
		if(next == array[cur_pos].symbol)
			return true;
	return false;
}

/* RomToArab: converts input roman numeral string to arabic numeral string and returns
	pointer to the resulting arabic numeral string; returns NULL if error.  It adds
	the value associated with each roman numeral symbol to the arabic number.  If the
	next roman numeral is in the string larger than the current one and the lead digit
	of the current one is 1 it subtracts the current roman numeral value instead. */
char* Translator::RomToArab(const char* t){
	if(!RomOrderIsGood(t))
		return nullptr;

	const char* s = t;
	int arab = 0;
	unsigned i = 0;
	while(*s && i >= 0 && i < ROM_NUM_SYM)
		if(*s == array[i].symbol){
			arab = ((jlib::LeadDigit(array[i].value) == 1) && peek(*(s+1), i)) ?
				arab - array[i].value : arab + array[i].value;
			s++;
		}
		else
			peek(*s, i) ? i-- : i++;
	if(i < 0 || i >= ROM_NUM_SYM)
		return nullptr;
	jlib::ItoB(arab, number_str, 10);
	return number_str;
}

/* ArabToRom: converts input arabic numeral string to roman numeral string and returns
	pointer to the resulting roman numeral string; returns NULL if error */
char* Translator::ArabToRom(const char* t){
	const char* p = t;
	while(*p)
		if(!isdigit(*p++))
			return nullptr;

	char* s = number_str;

	unsigned arab = atoi(t);
	if(arab > MAX_ARB || arab < 1)
		return nullptr;

	int i = 0;
	while(arab){
		if(arab >= array[i].value){
			int lDigit = jlib::LeadDigit(arab);	//if lead digit is 9 or 4 then chane in algorithm
			if((lDigit == 9 || lDigit == 4) && i){	//Prevents looking for a roman numeral greater than biggest
				int a = lDigit == 9 ? 1 : 0;	//a=1 if lDigit=9 and a=0 if lDigit=4
				*s++ = array[i + a].symbol;	//adds the next smallest symbol to the string if 9 or current if 4
				arab += array[i + a].value;	//adds value of next smallest to arabic
				*s++ = array[i - 1].symbol;	//adds the previous larger symbol to the string
				arab -= array[i - 1].value;	//subtracts value of the previous larger roman numeral from arabic
			}
			else{
				*s++ = array[i].symbol;		//Add the roman num symbol to the string
				arab -= array[i].value;		//Sub the value of the roman num from the arabic number
			}
		}
		else
			i++;
	}
	*s = '\0';

	return number_str;
}

/* Translate: determines whether input string is arabic or roman and routes to
		appropriate translation function.  Returns pointer to translated
		string, returns nullptr if translation failed. */
char* Translator::Translate(const char* t){
	if(isdigit(*t)){
		return ArabToRom(t);
	}
	else
		return RomToArab(t);
}

/* Translate: translates input string s to the opposite numeral type
	pointing input char* t to the translation.
	Returns 2 if the translation was arabic to roman.
	Returns 1 if the translation was roman to arabic.
	Returns 0 if the translation failed. */
int Translator::Translate(const char* s, char*& t){
	if(isdigit(*s)){
		t = ArabToRom(s);
		return t ? 2 : 0;
	}
	else{
		t = RomToArab(s);
		return t ? 1 : 0;
	}
}

/* RomOrderIsGood: Returns true if there are no errors in the order of symbols
	in the input roman numeral, false otherwise */
bool Translator::RomOrderIsGood(const char* s){
	int i = 0;
	bool lOne, lTen, lHund;
	lOne = lTen = lHund = false;
	while(*(s+1)){
		unsigned cur_val = getval(*s);
		unsigned next_val = getval(*(s+1));
		if(jlib::LeadDigit(cur_val) == 1){
			if(next_val > cur_val){
				unsigned a = jlib::rank(cur_val);
				unsigned b = jlib::rank(next_val);
				if(!(a == b || a + 1 == b))
					return false;
				if(i && (getval(*(s-1)) <= cur_val))
					return false;
				switch(cur_val){
				case 1:
					if(lOne)
						return false;
					lOne = true;
					break;
				case 10:
					if(lTen)
						return false;
					lTen = true;
					break;
				case 100:
					if(lHund)
						return false;
					lHund = true;
					break;
				};
			}
		}
		else
			if(getval(*(s+1)) > getval(*s))
				return false;
		i++;
		s++;
	}
	return true;
}

/* getval:  returns the value of the input roman numeral symbol; 0 if the input
	is not a valid symbol */
unsigned Translator::getval(char c){
	for(unsigned i = 0; i < ROM_NUM_SYM; i++)
		if(c == array[i].symbol)
			return array[i].value;
	return 0;
}
