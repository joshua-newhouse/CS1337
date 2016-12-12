#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cmath>
#include <iomanip>
#include "polyfunc.h"
#include "node.h"

/* Parse: Takes a polynomial function as a string and parses it into separate
	terms.  It dynamically creates a node for each term and passes it to
	the Insert method of terms, PolyFunc's instantiation of the List class.
	It also captures the preimage which is passed to the function:
	ex. f(X.XX)
	As it adds terms to the list it calculates the image of the function
	by adding the current coeficient * preimage ^ exponent to the previous
	value of the image */
void PolyFunc::Parse(std::string& line){
	preimage = atof(line.c_str() + 2);
	float sign = 1.0f;

	unsigned i;
	for(i = 5; line[i] != '='; i++)
		;
	i += 2;

	while(i < line.length()){
		switch(line[i]){
		case '-':
			sign = -1.0f;
			i++;
			break;
		case '+':
			sign = 1.0f;
			i++;
			break;
		case ' ':
			i++;
			break;
		default:
			Node* nptr = new Node();
			size_t len = line.length();

			nptr->coef = (line[i] == 'x' || line[i] == 'X') ?
				sign * 1.0f : sign * atof(line.c_str() + i);

			while(isdigit(line[i]) || line[i] == '.')
				i++;

			if(line[i] == 'x' || line[i] == 'X')
				nptr->exp = line[++i] == '^' ? atoi(line.c_str() + ++i) : 1;

			while(i < len && line[i] != ' ')
				i++;

			terms.Insert(nptr);
			image += nptr->coef * std::pow(preimage, nptr->exp);
		}
	}
}

/*Print: Takes and output stream as a parameter and writes the function to it
	in order of decreasing exponents then writes the image of the function
	applied to the preimage */
void PolyFunc::Print(std::ofstream& out){
	std::string line("f(");
	std::ostringstream oss;
	oss << preimage;
	line += oss.str() + ") = ";
	terms.Write(line, terms.GetHead());
	line += "= ";
	oss.str("");
	oss.clear();
	oss << std::fixed;
	oss << std::setprecision(3);
	oss << image;
	line += oss.str();
	out << line << std::endl;
}
