#include <string>
#include <sstream>
#include "node.h"
#include "list.h"

/* Insert: Takes a node pointer as a parameter and inserts it into the list
	by value of exponent.  Larger exponents go to the end of the list.
	If an exponent is added multiple times to the list then the coeficients
	are added together and placed in the node in the list, the second node
	is then deleted.	*/
void List::Insert(Node* n_ptr){
	if(!head)
		head = n_ptr;

	else{
		Node* lptr,* p_ptr;
		for(p_ptr = nullptr, lptr = head;
		    lptr; p_ptr = lptr, lptr = lptr->GetNext()){
			if(lptr->exp == n_ptr->exp){
				lptr->coef += n_ptr->coef;
				delete n_ptr;
				return;
			}
			else if(n_ptr->exp < lptr->exp){
				n_ptr->SetNext(lptr);
				if(p_ptr)
					p_ptr->SetNext(n_ptr);
				else
					head = n_ptr;
				return;
			}
		}
		p_ptr->SetNext(n_ptr);
	}
}

/* Write: Takes a string and a node pointer as parameters.  Recursively writes
	each term of the polynomial to the string beginning with the last term
	in the list(the one with the largest exponent). */
void List::Write(std::string& line, Node* nptr){
	static bool firstPass;
	if(nptr->GetNext()){
		firstPass = true;
		Write(line, nptr->GetNext());
	}
	
	if(!nptr->coef)
		return;

	if(nptr->coef > 0.0f){
		if(!firstPass)
			line += "+ ";
	}
	else
		line += "- ";
	if((nptr->coef - 1.0 && nptr->coef + 1.0) || !nptr->exp){
		std::ostringstream oss;
		nptr->coef = nptr->coef < 0.0 ?
			-1.0 * nptr->coef : nptr->coef;
		oss << nptr->coef;
		line += oss.str();
	}
	if(nptr->exp){
		line += 'x';
		if(nptr->exp > 1 || nptr->exp < 0){
			std::ostringstream oss;
			oss << nptr->exp;
			line += '^' + oss.str();
		}
	}
	line += ' ';
	firstPass = false;
}
