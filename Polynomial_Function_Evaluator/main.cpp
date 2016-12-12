#include <fstream>
#include <string>
#include "polyfunc.h"
#include "list.h"

/* Poly program
	Opens an input text file called "poly.txt" containing lines of
		functions that resemble polynomial functions
	Opens an output file called "answers.txt" to write output
	Loops though the input file reading each line and does the following:
		It creates a PolyFunc object which is used to parse the line
			into a list of terms of the function and evaluate it
		The PolyFunc object then writes the evaluated function to the
			output file that is passed to it
	Finally the program closes all files	*/
int main(){
	std::ifstream input("poly.txt");
	std::ofstream output("answers.txt");
	std::string line;

	while(std::getline(input, line)){
		PolyFunc pf;
		pf.Parse(line);
		pf.Print(output);
	}

	input.close();
	output.close();

	return 0;
}
