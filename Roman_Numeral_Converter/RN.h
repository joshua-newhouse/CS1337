/* RNConverter class is responsible for:
	- Converting numerals between roman and arabic
		May convert single numeral or entire file with list of numerals

	- Creating and maintaining a sorted list of the numerals in the file
	  being translated
		May manipulate this list by:
			- Adding a numeral to the list
			- Deleting a specified numeral from the list
			- Deleting the first numeral from the list
			- Deleting the last numeral from the list

	- Searching the list for a specified numeral

	- Writing the list to an output file
*/

#ifndef RH_H
#define RH_H

#include "Parser.h"
#include "Translator.h"
#include "list.h"

class RNConverter{
	private:
		Parser parser;
		Translator translator;
		List list;

	public:
		char* Convert(const char*);
		void ConvertFile(const char*);
		void CreateList(const char*);
		bool Search(const char*);
		void WriteList(const char*);
		void AddToList(const char*);
		void DeleteFromList(const char*);
		void TrimHead(){
			--list;
		}
		void TrimTail(){
			list--;
		}
};

#endif
