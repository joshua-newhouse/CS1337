#ifndef PARSER_H
#define PARSER_H

class Parser{
	private:
		const unsigned ARB_BEG_POS; //Begin position of arabic numeral in string
		const unsigned ARB_END_POS; //End position of arabic numeral in string

	public:
		Parser();
		char* Parse(char*);
		char* Unparse(char*, const char*);
		char* Build(const char*, const char*);
};

#endif

/* Parse class is responsible for extracting the numeral substring
	(roman or arabic) from the input string.  It is also
	responsible for putting the translated numeral substring
	back into the original string and building a string from
	scratch using the roman and arabic numerals.
*/
