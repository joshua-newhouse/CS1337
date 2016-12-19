/* BaseNode Abstract Class:
	Private members
		string to hold the roman numeral
		string to hold the arabic numeral
	Public members
		Default constructor
		Initialization constructor
		Copy constructor

		Getter for roman numeral
		Getter for arabic numeral

		Setter for roman numeral
		Setter for arabic numeral

		Overloaded << operator for stream output
		Overloaded == operator
		Overloaded < operator

		Virtual function to display the status of the node
*/

/* DoubleLinkNode Class:  Inherits from BaseNode abstract class
	Private members
		pointer to the next DoubleLineNode
		pointer to the previous DoubleLineNode
	Public members
		Default constructor
		Initialization constructor
		Copy constructor

		Getter for next node
		Getter for previous node

		Setter for next node
		Setter for previous node

		Overloaded virtual function from BaseNode class that displays
			the status of the current node
*/

#ifndef NODE_H
#define NODE_H

#include <string>
#include <cstdlib>
#include <iostream>

class BaseNode{
	private:
		std::string roman;
		std::string arabic;

	public:
		BaseNode() : roman(""), arabic("")
		{}
		BaseNode(const std::string r, const std::string a){
			roman = r;
			arabic = a;
		}
		BaseNode(const BaseNode& n){
			if(&n){
				roman = n.roman;
				arabic = n.arabic;
			}
			else
				arabic = roman = "";
		}
		virtual ~BaseNode()
		{}

		std::string GetRom(){
			return roman;
		}
		std::string GetArab(){
			return arabic;
		}

		void SetRom(const std::string s){
			roman = s;
		}
		void SetArab(const std::string s){
			arabic = s;
		}

		friend std::ostream& operator<<(std::ostream&, const BaseNode&);

		/* operator==: returns true if argument BaseNode arabic numeral
			is equal to this node arabic numeral, false otherwise */
		bool operator==(const BaseNode& n) const{
			if(&n == nullptr)
				return false;
			return arabic == n.arabic;
		}

		/* operator<: returns true if argument BaseNode arabic numeral
			is greater than this node arabic numeral, else false */
		bool operator<(const BaseNode& n) const{
			if(&n == nullptr)
				return false;
			return atoi(arabic.c_str()) < atoi(n.arabic.c_str());
		}

		virtual void DisplayStatus() = 0;
};

class DoubleLinkNode : public BaseNode{
	private:
		DoubleLinkNode* next;
		DoubleLinkNode* prev;

	public:
		DoubleLinkNode() : next(nullptr), prev(nullptr)
		{}
		DoubleLinkNode(const std::string r, const std::string a) :
			BaseNode(r, a), next(nullptr), prev(nullptr)
		{}
		DoubleLinkNode(const BaseNode& b) :
			BaseNode(b), next(nullptr), prev(nullptr)
		{}

		DoubleLinkNode* GetNext(){
			return next;
		}
		DoubleLinkNode* GetPrev(){
			return prev;
		}

		void SetNext(DoubleLinkNode* n_ptr){
			next = n_ptr;
		}
		void SetPrev(DoubleLinkNode* n_ptr){
			prev = n_ptr;
		}

		/* DisplayStatus:  Writes information about the node to the
			stdout */
		void DisplayStatus(){
			std::cout << GetRom() << std::endl
				<< GetArab() << std::endl
				<< prev << std::endl
				<< next << std::endl;
		}
};

#endif
