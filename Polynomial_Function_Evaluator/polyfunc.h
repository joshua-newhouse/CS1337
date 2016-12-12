#ifndef POLYFUNC_H
#define POLYFUNC_H

#include <string>
#include <fstream>
#include "list.h"

/* PolyFunc class
	Contains a preimage of the function
	Contains the image of the function
	Contains a List of the terms in the function
	Has a Parse function which parses functions written as strings
		into their separate terms
	Has a Print function which writes the evaluated function to a file */
class PolyFunc{
	private:
		double preimage;
		double image;
		List terms;

	public:
		PolyFunc() : preimage(0.0), image(0.0)
		{}
		void Parse(std::string&);
		void Print(std::ofstream&);

};

#endif
