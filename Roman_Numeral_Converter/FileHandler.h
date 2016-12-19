#ifndef FH_H
#define FH_H

#include <fstream>

class FileHandler{
	private:
		const char* fileName;	//Name of file assosited with the file handler object
		std::fstream file;	//The open file stream being used by the fh object
		std::streampos write;	//The position in the file where the fh object will write

	public:
		FileHandler(const char*, int);
		~FileHandler();
		bool ReadLine(char*, std::streamsize);
		void WriteLine(const char*, bool);
		void Write(const char* buf){
			file << buf;
		}
};

#endif

/* FileHandler class handles opening of file for IO.

   Contains a string "fileName", an fstream "file", and streampos write.
   fileName contains the name of the file.
   file holds the stream object.
   write holds the position in the file where the write operation will occur

   Constructor opens the file given the file name
   Destructor closes the file
   ReadLine reads the next line of the file up to streamsize characters
	and stores it in its first parameter; it returns true if there are
	no errors and the eof has not been encountered, false otherwise
   WriteLine writes the string in its parameter to the file.  The write
	position is set to the beginning of the last line read by ReadLine.
*/
