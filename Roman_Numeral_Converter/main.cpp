// DELETE ANY NODE EXTRA CREDIT

#include <iostream>
#include <cstdlib>
#include <climits>
#include <cctype>
#include "RN.h"

#ifdef __linux__
	#define CLR_SCR() system("clear")
#else
	#define CLR_SCR() system("cls")
#endif

enum procType {SEARCH, ADD, DELETE};
void Procedure(RNConverter&, const std::string&, procType);

/* Converter program: Creates a roman numeral converter.
	If filenames are provided through the command line then
	it runs the converter on the specified files; otherwise it
	runs the converter UI on the default "numbers.txt" */
int main(int argc, char* argv[]){
	RNConverter rn;

	if(argc > 1){
		for(int i = 1; i < argc; i++)
			rn.ConvertFile(argv[i]);
		exit(EXIT_SUCCESS);
	}

	rn.CreateList("numbers.txt");

	while(1){
		std::cout << "Enter the number of your selection and press ENTER\n"
			<< "1. Search list of numerals\n"
			<< "2. Add numeral to list\n"
			<< "3. Delete first numeral from list\n"
			<< "4. Delete last numeral from list\n"
			<< "5. Delete specific numeral from list\n"
			<< "6. Exit\n";

		char ch;
		std::cin >> ch;
		std::cin.ignore(INT_MAX, '\n');

		switch(ch){
		case '1':
			Procedure(rn, "Enter numeral to search for", SEARCH);
			break;
		case '2':
			Procedure(rn, "Enter numeral to add", ADD);
			break;
		case '3':
			rn.TrimHead();
			break;
		case '4':
			rn.TrimTail();
			break;
		case '5':
			Procedure(rn, "Enter numeral to delete", DELETE);
			break;
		case '6':
			rn.WriteList("numbers.txt");
			exit(EXIT_SUCCESS);
		default:
			std::cout << "Invalid selection\n";
		};

		std::cout << "Press ENTER to continue\n";
		std::cin.get();
		CLR_SCR();
	}

	return 0;
}

/* Procedure:
	This runs the UI for searching, adding to, and deleting specific
	numerals from the list.  It prompts the	user for the numeral then calls
	converts the input to uppercase if a roman numeral and then calls the
	appropriate RNConverter method. */
void Procedure(RNConverter& rn, const std::string& msg, procType t){
	std::string term;
	std::cout << msg << std::endl;
	std::cin >> term;
	std::cin.ignore(INT_MAX, '\n');
	if(isalpha(term[0]))
		for(unsigned i = 0; i < term.length(); i++)
			term[i] = toupper(term[i]);
	switch(t){
	case SEARCH:
		if(rn.Search(term.c_str()))
			std::cout << term << " is present in the list\n";
		else
			std::cout << term << " is not in the list\n";
		break;
	case ADD:
		rn.AddToList(term.c_str());
		break;
	case DELETE:
		rn.DeleteFromList(term.c_str());
	};
}
