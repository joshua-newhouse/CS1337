#include <fstream>
#include <iostream>
#include <cstdlib>
#include "FileHandler.h"

/* FileHandler: Constructor initializes NUMBER, header string, and allocates space for the input string
		and opens files for input/output */
FileHandler::FileHandler(const char* in, const char* out) : NUMBER(9), header(NULL) {
	input.open(in);
	if(input)
		std::cout << "Opened " << in << std::endl;
	else
		std::cout << "Error opening " << in << std::endl;

	output.open(out);
	if(output)
		std::cout << "Opened " << out << std::endl;
	else
		std::cout << "Error opening " << out << std::endl;

	iString = new char[NUMBER * NUMBER]();
}

/* ~FileHandler: Destructor closes the file and frees allocated mem */
FileHandler::~FileHandler(){
	delete[] iString;
	delete[] header;
	input.close();
	output.close();
	std::cout << "Closed files.\n";
}

/* GetData: Allocates space for  header and grabs it from the file.
	Then reads the char data into the iString discarding newline chars;
	returns iString */
char* FileHandler::GetData(){
	if(!input)
		return NULL;

	if(header)
		delete[] header;
	header = new char[10]();
	input >> header;

	for(unsigned i = 0; i < NUMBER * NUMBER; i++)
		input >> std::skipws >> *(iString + i);

	char ch;
	input >> std::skipws >> ch;
	input.putback(ch);

        return iString;
}
