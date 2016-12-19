/* List class is responsible for:
	- Creating and maintaining a linked list of DoubleLinkNode objects
		Tracks the size of the list
		Maintains a pointer to the head of the list
		Maintains a pointer to the tail of the list
		Maintains a current pointer for working with nodes in the list
		Adding a node to the end of the list
		Removing a node from the beginning of the list
		Removing a node from the end of the list
		Removing a specified node from anywhere in the list
		Swapping nodes in the list
	- Sorting the list by ascending node
	- Performing a binary search of the list for a specified node
	- Deleting the list
	- Searching the list for a specified node
	- Writing the list to an output stream
*/

#ifndef LIST_H
#define LIST_H

#include "node.h"

class List{
	private:
		DoubleLinkNode* head;
		DoubleLinkNode* tail;
		DoubleLinkNode* cur_ptr;
		size_t size;

		void DeleteList(DoubleLinkNode*);
		void SwapNodes(DoubleLinkNode*, DoubleLinkNode*);

	public:
		List() : head(nullptr), tail(nullptr), cur_ptr(nullptr), size(0)
		{}
		List(DoubleLinkNode& n){
			cur_ptr = tail = head = new DoubleLinkNode(n);
			size = 1;
		}
		~List(){
			if(head){
				DeleteList(head);
				size = 0;
				cur_ptr = tail = head = nullptr;
			}
		}

		DoubleLinkNode* GetHead(){
			return head;
		}
		DoubleLinkNode* GetTail(){
			return tail;
		}
		size_t Size(){
			return size;
		}

		List& operator+=(const DoubleLinkNode&);
		List& operator--();
		List& operator--(int);
		List& operator-(const DoubleLinkNode&);
		void Delete(DoubleLinkNode*);
		friend List& operator>>(DoubleLinkNode& n, List& l){
			return l += n;
		}
		List& operator++(int);
		void Sort();
		friend List& operator<<(std::ostream&, List&);
		bool BinSrch(const DoubleLinkNode&);
};

#endif
