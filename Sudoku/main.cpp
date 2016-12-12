#include "FileHandler.h"
#include "Validator.h"

int main(){
	FileHandler fh("puzzles.txt", "solutions.txt");	//Creates FileHandler

	/* Writes table header to file */
	fh.WriteOutput("PUZZLE    VALIDITY   "
			"LOCATION OF 1st ERROR; DUPLICATED/OMMITTED NUMBERS");

	/* Loops through each puzzle in the input file.  Terminates at EOF or read error
	   Creates a Validator initialized with the puzzle number and the puzzle board.
	   FileHandler WriteOutput method is call to write the results of the Validator's
	   Validate method */
	while(fh.GetData()){
		Validator vl(fh.header, fh.iString);
		fh.WriteOutput(vl.Validate());
	}

	return 0;
}
