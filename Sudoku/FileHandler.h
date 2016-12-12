#ifndef FH_H
#define FH_H

#include <fstream>

class FileHandler{
	private:
		std::ifstream input;	//Input file stream
		std::ofstream output;	//Output file stream
		const unsigned NUMBER;	//Square root of number of characters to read

	public:
		char* header;		//Pointer to first line of input
		char* iString;		//Pointer to array of characters read from file

		/* Constructor: opens input and output streams and initializes NUMBER
		   Allocates memory for iString */
		FileHandler(const char*, const char*);

		/* Destructor: closes files and deletes memory allocated for header and
		   iString */
		~FileHandler();

		/* GetData: reads input file into header and iString.  Allocates memory
		   for header.  Returns NULL if EOF or read error, returns pointer to
		   iString otherwise */
		char* GetData();

		/* WriteOutput: writes string s to the output file stream */
		void WriteOutput(const char* s){
			output << s << std::endl;
		}
};

#endif
