#ifndef NODE_H
#define NODE_H

/* Node class
	Contains a private node pointer to point at the next node in the list
	Contains a public coeficient and public exponent
	Has a default constructor which sets all data members to 0
	Has a constructor which creates a node given the coefficient and
		exponent as parameters
	Has an accessor function GetNext which returns the private node pointer
		next
	Has a mutator SetNext which sets the node pointer next	*/

class Node{
	private:
		Node* next;

	public:
		double coef;
		int exp;

		Node() : next(nullptr), coef(0.0), exp(0)
		{}
		Node(double c, int e) : next(nullptr){
			coef = c;
			exp = e;
		}

		Node* GetNext(){
			return next;
		}
		void SetNext(Node* nptr){
			next = nptr;
		}
};

#endif
