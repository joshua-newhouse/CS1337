#include <fstream>
#include <iostream>
#include <cstdlib>
#include "FileHandler.h"

/* FileHandler: Constructor initializes fileName and opens file for input/output if i != 0;
		opens file for output/truncate if i = 0. */
FileHandler::FileHandler(const char* fName, int i) : write(0) {
	fileName = fName;
	i ? file.open(fileName, std::ios::in | std::ios::out) :
		file.open(fileName, std::ios::out | std::ios::trunc);
	if(file.is_open() && file.good())
		std::cout << "Opened " << fileName << std::endl;
	else
		std::cout << "Error opening " << fileName << std::endl;
}

/* ~FileHandler: Destructor closes the file */
FileHandler::~FileHandler(){
	file.close();
	std::cout << "Closed " << fileName << std::endl;
}

/* ReadLine: Puts position of the beginning of the current line into write then
		reads the current line into buf; returns true if no errors or
		eof, false otherwise */
bool FileHandler::ReadLine(char* buf, std::streamsize n){
        write = file.tellg();
        return file.getline(buf, n);
}

/* WriteLine: Sets the write file pointer to the beginning of the last line
		read by ReadLine then writes buf to the file.  If the EOF
		was reached by ReadLine on the previous read, WriteLine clears
		the eof flag and writes the final line without a newline char */
void FileHandler::WriteLine(const char* buf, bool writeInPlace){
        if(file.eof()){
                file.clear();
                file.seekp(write);
                file << buf;
        }
        else{
                if(writeInPlace)
			file.seekp(write);
                file << buf << std::endl;
        }
}
