#ifndef TRANS_H
#define TRANS_H

const unsigned MAX_NUM_LEN = 16;	//max length of numeral string
const unsigned ROM_NUM_SYM = 7;		//number of available roman numerals
const unsigned MAX_ARB = 4999;		//max arabic numeral

/* Roman numeral type: ex. 'M', 1000 */
typedef struct{
	char symbol;
	unsigned value;
} romNum_ts;

class Translator{
	private:
		char number_str[MAX_NUM_LEN + 1];	//String to hold translation
		const romNum_ts array[ROM_NUM_SYM];	//Array of roman numeral symbols available
		void DisplaySym();
		bool peek(char, int);
		char* RomToArab(const char*);
		char* ArabToRom(const char*);
		bool RomOrderIsGood(const char*);
		unsigned getval(char);

	public:
		Translator();
		char* Translate(const char*);
		int Translate(const char*, char*&);
};

#endif

/* Translator class is responsible for translating an
	input numeral string (arabic or roman) into 
	a numeral string of the opposite type.  It contains
	an array of roman numeral structures which
	represent the available roman numerals for translation.
*/
	
