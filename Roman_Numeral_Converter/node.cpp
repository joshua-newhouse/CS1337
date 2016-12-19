#include <string>
#include <iostream>
#include "node.h"

/* operator<<:  Overloads the << operator for the BaseNode class
	Parameters
		std::ostream&
		const BaseNode&
	Function
		Writes BaseNode string members roman and arabic to the ostream
			parameter with the proper formatting
	Returns
		std::ostream& passed in as first parameter
*/
std::ostream& operator<<(std::ostream& os, const BaseNode& n){
	if(&n == nullptr)
		return os;
	os << n.roman;
	for(int i = n.roman.length(); i < 16; i++)
		os << ' ';
	os << n.arabic;
	for(int i = n.arabic.length(); i < 4; i++)
		os << ' ';
	return os;
}
