#include <iostream>
#include "list.h"
#include "node.h"

/* DeleteList:
	Parameters
		DoubleLinkNode* - call function with head node as argument
	Function
		Recursively deletes each node in the list
	Invalid input
		nullptr - no error checking, will cause crash
	Returns
		void
*/
void List::DeleteList(DoubleLinkNode* n_ptr){
	if(n_ptr->GetNext())
		DeleteList(n_ptr->GetNext());
	delete n_ptr;
}

/* operator+=:
	Parameters
		const DoubleLinkNode& - node to be added to list
	Function
		Dynamically creates a new node copied from the input
		Adds the new node to the end of the list
		Increments the list size
	Invalid input
		none
	Returns
		List& - a reference to this list
*/
List& List::operator+=(const DoubleLinkNode& n){
	if(tail){
		tail->SetNext(new DoubleLinkNode(n));
		tail->GetNext()->SetPrev(tail);
		tail = tail->GetNext();
	}
	else
		tail = head = new DoubleLinkNode(n);

	size++;
	return *this;
}

/* operator--:
	Parameters
		none
	Function
		Deletes the first node in the list (node pointed to by head)
		Moves head to the next node or nullptr if none
		Decrements the list size
	Invalid input
		none
	Returns
		List& - a reference to this list
*/
List& List::operator--(){
	DoubleLinkNode* temp = head;
	if(head){
		if(cur_ptr == head)
			cur_ptr = head->GetNext();
		head = head->GetNext();
		if(head)
			head->SetPrev(nullptr);
		else
			tail = nullptr;
		delete temp;
		size--;
	}
	return *this;
}

/* operator--(int):
	Parameters
		none
	Function
		Deletes the last node in the list (node pointed to by tail)
		Moves tail to the previous node or nullptr if none
		Decrements the list size
	Invalid input
		none
	Returns
		List& - a reference to this list
*/
List& List::operator--(int){
	DoubleLinkNode* temp = tail;
	if(tail){
		if(cur_ptr == tail)
			cur_ptr = head;
		tail = tail->GetPrev();
		if(tail)
			tail->SetNext(nullptr);
		else
			head = nullptr;
		delete temp;
		size--;
	}
	return *this;
}

/* operator-:
	Parameters
		const DoubleLinkNode& - node to search for and remove from list
	Function
		Moves through list locating all nodes matching the input node
		Deletes matching nodes from list
	Invalid input
		none
	Returns
		List& - a reference to this list
*/
List& List::operator-(const DoubleLinkNode& n){
	DoubleLinkNode* n_ptr = head;
	for(; n_ptr; n_ptr = n_ptr->GetNext())
		if(*n_ptr == n)
			Delete(n_ptr);
	return *this;
}

/* Delete:
	Parameters
		DoubleLinkNode* - pointer to node in list to delete
	Function
		Links previous node to the next node and vice versa
		Deletes the node pointed to by the input pointer
		Decrements the list size
	Invalid input
		nullptr - no error checking, will cause crash
	Returns
		void
*/
void List::Delete(DoubleLinkNode* n_ptr){
	if(n_ptr->GetPrev())
		n_ptr->GetPrev()->SetNext(n_ptr->GetNext());
	else
		head = n_ptr->GetNext();

	if(n_ptr->GetNext())
		n_ptr->GetNext()->SetPrev(n_ptr->GetPrev());
	else
		tail = n_ptr->GetPrev();

	delete n_ptr;
	size--;
}

/* operator++(int):
	Parameters
		none
	Function
		Moves curr_ptr to next node in the list.  Loops back to head if
			at tail
	Invalid input
		none
	Returns
		List& - a reference to this list
*/
List& List::operator++(int){
	if(!cur_ptr && head)
		cur_ptr = head;
	cur_ptr = cur_ptr == tail ? head : cur_ptr->GetNext();
	return *this;
}

/* SwapNodes:
	Parameters
		DoubleLinkNode* n_ptr1 - node closest to head to be swapped
		DoubleLinkNode* n_ptr2 - node closest to tail to be swapped
	Function
		Swaps node pointed to by first param with node pointed to by
			second param
	Invalid input
		nullptr in either parameter - no error checkin, will cause crash
	Returns
		void
*/
void List::SwapNodes(DoubleLinkNode* n_ptr1, DoubleLinkNode* n_ptr2){
	bool adjacent = n_ptr1->GetNext() == n_ptr2;

	if(head == n_ptr1)
		head = n_ptr2;
	if(tail == n_ptr2)
		tail = n_ptr1;


	if(n_ptr1->GetPrev())
		n_ptr1->GetPrev()->SetNext(n_ptr2);
	if(n_ptr2->GetNext())
			n_ptr2->GetNext()->SetPrev(n_ptr1);
	if(!adjacent){
		n_ptr1->GetNext()->SetPrev(n_ptr2);
		n_ptr2->GetPrev()->SetNext(n_ptr1);
	}

	DoubleLinkNode* temp = n_ptr2->GetNext();
	adjacent ? n_ptr2->SetNext(n_ptr1) : n_ptr2->SetNext(n_ptr1->GetNext());
	n_ptr1->SetNext(temp);

	temp = n_ptr2->GetPrev();
	n_ptr2->SetPrev(n_ptr1->GetPrev());
	adjacent ? n_ptr1->SetPrev(n_ptr2) : n_ptr1->SetPrev(temp);
}

/* Sort:
	Parameters
		none
	Function
		Performs bubble sort of list ordering nodes in ascending order
	Invalid input
		none
	Returns
		void
*/
void List::Sort(){
	if(size < 2)
		return;

	bool repeat;
	do{
		repeat = false;
		for(DoubleLinkNode* n_ptr1 = head,* n_ptr2 = head->GetNext();
			n_ptr2; n_ptr1 = n_ptr1->GetNext(), n_ptr2 = n_ptr2->GetNext())
			if(*n_ptr2 < *n_ptr1){
				SwapNodes(n_ptr1, n_ptr2);
				repeat = true;
				n_ptr1 = head;
				n_ptr2 = head->GetNext();
			}
	}while(repeat);
	cur_ptr = head;
}

/*operator<<: *Recursive function call*
	Parameters
		std::ostream& - output stream to write list to
		List& - referense to this list
	Function
		Writes node pointed to by cur_ptr to ostream
		Moves cur_ptr to next node in list
		Recursively calls << operator
	Invalid input
		none
	Returns
		List& - a reference to this list
*/
List& operator<<(std::ostream& os, List& l){
	static unsigned count = 0;
	if(count < l.Size()){
		os << *l.cur_ptr << std::endl;
		l++;
		count++;
		os << l;
	}
	count = 0;
	return l;
}

/*BinSrch: The list must be sorted prior to performing a binary search; function
	does not check for this.  Will crash if called on unsorted list.
	Parameters
		const DoubleLinkNode& - node to search for in list
	Function
		Performs binary search of the items in the list
	Invalid input
		none
	Returns
		bool - true if node found in list, false otherwise
*/
bool List::BinSrch(const DoubleLinkNode& n){
	int beg = 0, end = size - 1;

	while(beg <= end){
		int mid = (end + beg) / 2;

		DoubleLinkNode* n_ptr = head;
		for(int i = 0; i < mid; i++, n_ptr = n_ptr->GetNext())
			;

		if(n == *n_ptr)
			return true;
		else if(n < *n_ptr)
			end = mid - 1;
		else
			beg = mid + 1;
	}

	return false;
}
