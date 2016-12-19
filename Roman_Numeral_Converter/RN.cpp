#include <iostream>
#include <sstream>
#include "RN.h"
#include "FileHandler.h"
#include "Parser.h"
#include "Translator.h"
#include "list.h"
#include "node.h"

/* ConvertFile: Performs roman/arabic numeral converion on input file, fileName
   Creates a filehandler and a string buffer to use for passing line of file
   between the parser, translator, and filehandler.  The filehandler reads the
   next line and sends it to the parser.  The parser parses out the numeral from
   the line then passes it along to the translator.  The translator translates
   the numeral from its current type (arabic or roman) to the opposite type then
   passes it back to the parser.  The parser aligns the final string for the file
   and passes it back to the filehandler.  Finally, the filehandler writes the
   buffer back to the file.  This process is repeated for each line in the file */
void RNConverter::ConvertFile(const char* fileName){
	FileHandler fh(fileName, 1);
	const std::streamsize LEN = 21;
	char string[LEN];
	char* c_ptr = nullptr;
	unsigned lNumber = 0;

	while(fh.ReadLine(string, LEN)){
		lNumber++;
		if((c_ptr = parser.Parse(string)) == nullptr){
			std::cout << "Error parsing " << fileName
					<< " line " << lNumber << std::endl;
			continue;
		}
		if((c_ptr = translator.Translate(c_ptr)) == nullptr){
			std::cout << "Error translating " << fileName
					<< " line " << lNumber << std::endl;
			continue;
		}
		fh.WriteLine(parser.Unparse(string, c_ptr), true);
	}
}

/* Convert: Performs roman/arabic numeral conversion on input string returning
	a pointer to the translated string. */
char* RNConverter::Convert(const char* numeral){
	return translator.Translate(numeral);
}

/* CreateList: Creates a List of numerals in the input file (fileName).
	Any input errors in the file are skipped, therefore the resulting
	list has only valid roman/arabic numeral pairs. */
void RNConverter::CreateList(const char* fileName){
	const std::streamsize LEN = 21;
	char string[LEN];
	char* s = nullptr, * t = nullptr;
	unsigned lNumber = 0;
	FileHandler fh(fileName, 1);
	int a = 0;

	while(fh.ReadLine(string, LEN)){
		lNumber++;
		if((s = parser.Parse(string)) == nullptr){
			std::cout << "Error parsing " << fileName
					<< " line " << lNumber << std::endl;
			continue;
		}
		if((a = translator.Translate(s, t)) == 0){
			std::cout << "Error translating " << fileName
					<< " line " << lNumber << std::endl;
			continue;
		}
		DoubleLinkNode dn = a == 1 ? DoubleLinkNode(s, t) : DoubleLinkNode(t, s);
		dn >> list;
	}
	list.Sort();
}

/* Search:  Takes a string as input.  It searches its list
	for the input string "term".  Returns true if the term is found
	false otherwise. */
bool RNConverter::Search(const char* term){
	char* c = nullptr;
	int a = 0;

	if((a = translator.Translate(term, c)) == 0){
		std::cout << "Invalid numeral\n";
		return false;
	}
	DoubleLinkNode dn = a == 1 ? DoubleLinkNode(term, c) : DoubleLinkNode(c, term);
	return list.BinSrch(dn);
}

/* AddToList:
	Parameters
		const char* (c-string) - numeral to be added to the list; may be
			a 4 digit arabic numeral or 15 digit roman numeral
	Function
		Translates input numeral string into a numeral string of the
			opposite type (arabic or roman)
		Creates a new DoubleLinkNode containing both numeral strings
		Inserts the new node into the list
	Invalid input
		A string that cannot be translated.  Writes error message to
			stdout then returns to caller without adding a new node
			to list
	Output
		none
	Returns
		void
*/
void RNConverter::AddToList(const char* term){
	char* c = nullptr;
	int a = 0;

	if((a = translator.Translate(term, c)) == 0){
		std::cout << "Invalid numeral; not added to list.\n";
		return;
	}
	DoubleLinkNode dn = a == 1 ? DoubleLinkNode(term, c) : DoubleLinkNode(c, term);
	dn >> list;
	list.Sort();
}

/* DeleteFromList:
	Parameters
		const char* (c-string) - numeral to be deleted from the list
	Function
		Translates input numeral string into a numeral string of the
			opposite type (arabic or roman)
		Creates a new DoubleLinkNode containing both numeral strings
		Deletes any nodes in the list that equal the created node
	Invalid input
		A string that cannot be translated.  Writes error message to
			stdout then returns to caller
	Output
		Error message to stdout if invalid input
		Message to stdout if numeral was deleted from list
		Message to stdout if numeral was not present in list
	Returns
		void
*/
void RNConverter::DeleteFromList(const char* term){
	char* c = nullptr;
	int a = 0;

	if((a = translator.Translate(term, c)) == 0){
		std::cout << "Invalid numeral; not in list.\n";
		return;
	}
	DoubleLinkNode dn = a == 1 ? DoubleLinkNode(term, c) : DoubleLinkNode(c, term);
	unsigned preSize = list.Size();
	list - dn;
	if(preSize - list.Size())
		std::cout << term << " deleted from list\n";
	else
		std::cout << term << " not in list\n";
}

/* WriteList: Takes a file name as input.  Writes the current list contents
	to the specified file, overwriting the contents of the file. */
void RNConverter::WriteList(const char* fileName){
	FileHandler fh(fileName, 0);
	std::ostringstream os;
	
	os << list;
	fh.Write(os.str().c_str());
}
