#ifndef LIST_H
#define LIST_H

#include <string>
#include "node.h"

/* List class
	Has a private node pointer, head, which points at the first node in
		the list
	Has a default constructor which sets head pointer to NULL
	Has a constructor that takes a node pointer as a parameter and uses it
		to set head
	Has a delete function which takes a node pointer as a parameter and
		recursively deletes all nodes in the list
	Has a destructor which calls the delete function
	Has an accessor function, GetHead, which returns the head pointer
	Has an Insert function which inserts a node into the proper place in
		the list
	Has a write function which recursively writes each node to the input
		string	*/
class List{
	private:
		Node* head;

	public:
		List() : head(nullptr)
		{}
		List(Node* nptr){
			head = nptr;
		}

		void Delete(Node* nptr){
			if(nptr->GetNext())
				Delete(nptr->GetNext());
			delete nptr;
		}
		~List(){
			Delete(head);
		}

		Node* GetHead(){
			return head;
		}

		void Insert(Node*);
		void Write(std::string&, Node*);
};
#endif
