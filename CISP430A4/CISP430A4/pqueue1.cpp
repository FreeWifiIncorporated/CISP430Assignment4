#include <stdlib.h>
#include <cassert>
#include <iostream>
#include "pqueue1.h"

using namespace std;

typedef int Item;

PriorityQueue::PriorityQueue()
{
	// Initialize an empty queue.
	head_ptr = NULL;
	many_nodes = 0;
}

PriorityQueue::PriorityQueue(const PriorityQueue & source)
{
	// If source is an empty queue, then...
	many_nodes = source.many_nodes;         // copy node count

	Node * node1 = NULL;                    // declare node pointer
	Node * precursor = NULL;                // declare precursor for new list 
	Node * copycursor = NULL;               // declare cursor for copy list

	copycursor = source.head_ptr;           // set copy cursor to source head

	int x = 0;
	while (x < many_nodes)               // start a loop for num of nodes
	{
		node1 = new Node;               // point node1 to a new allocated node

		node1->data = copycursor->data;         // copy over data to that node
		node1->priority = copycursor->priority;

		if (copycursor == source.head_ptr)      // if we're at the head
			head_ptr = node1;               // set new head to copy head

		if (precursor != NULL)               // if this isn't the first iteration
			precursor->link = node1;            // link the last node to this new node

		precursor = node1;              // precursor is now on this node
		copycursor = copycursor->link;          // copy cursor is now advanced

		x++;
	}
}

PriorityQueue::~PriorityQueue()
{

	if (many_nodes == 0)
	{
		head_ptr = NULL;
		return;
	}

	while (head_ptr != NULL)
	{
		Node *temp = head_ptr;
		head_ptr = head_ptr->link;
		delete temp;
	}
	many_nodes = 0;
}

void PriorityQueue::operator=(const PriorityQueue & source)
{

	if (this == &source) // Checks if the two queue are already the same.
	{
		return;
	}

	if ((source.head_ptr == NULL) && (head_ptr != NULL))
	{
		Node *temp;
		while (head_ptr != NULL)
		{
			temp = head_ptr;
			head_ptr = head_ptr->link;
			delete temp;
		}
	}
	
	if (source.head_ptr != NULL)
	{
		many_nodes = source.many_nodes;         // copy node count

		Node * node1 = NULL;                    // declare node pointer
		Node * precursor = NULL;                // declare precursor for new list 
		Node * copycursor = NULL;               // declare cursor for copy list

		copycursor = source.head_ptr;           // set copy cursor to source head

		int x = 0;
		while (x < many_nodes)               // start a loop for num of nodes
		{
			node1 = new Node;               // point node1 to a new allocated node

			node1->data = copycursor->data;         // copy over data to that node
			node1->priority = copycursor->priority;

			if (copycursor == source.head_ptr)      // if we're at the head
				head_ptr = node1;               // set new head to copy head

			if (precursor != NULL)               // if this isn't the first iteration
				precursor->link = node1;            // link the last node to this new node

			precursor = node1;              // precursor is now on this node
			copycursor = copycursor->link;          // copy cursor is now advanced

			x++;
		}
	}
}

void PriorityQueue::insert(const Item & entry, unsigned int priority)
{
	// Inserts a a copy of entry into the queue at the designated priority.
	// If there is no items in the queue, then entry is inserted at the front of the queue.
	// If there is already an existing item with the same priority in the queue, then the new entry is inserted behind that item.

	Node *temp, *q; // Creates pointers to hold temporary versions of the given entry and priority for use in function.
	temp = new Node;
	temp->data = entry;
	temp->priority = priority;

	if (head_ptr == NULL || priority > head_ptr->priority) // Checks if head_ptr points to NULL or if given priority is less than the priority of the head_ptr item.
	{
		// If head_ptr points to NULL, then there are no items in the queue.
		// Or, if the given priority is greater than the priority of the head_ptr item, then... 
		temp->link = head_ptr; // Assign address pointed to by head_ptr to the temp link pointer.
		head_ptr = temp; // Then assign value stored in temp to head_ptr to ensure the head_ptr points at the front value.
	}
	else // Else, there are items in the queue and the new entry must be inserted at the appropriate priority location.
	{
		q = head_ptr;
		while (q->link != NULL && q->link->priority >= priority)
		{
			q = q->link;
		}
		temp->link = q->link;
		q->link = temp;
	}

	++many_nodes;
}

Item PriorityQueue::get_front()
{
	// Gets the item at the front of the queue (the item with the highest priority), returns it to call, and removes it from the queue.

	// Assert that the size is greater than 0.
	assert(size() > 0);

	// Determine which item has the highest priority.
	// If multiple items have the same priority, then the first item in is returned.
	Node *temp;
	Item info;

	temp = head_ptr; // head_ptr should be pointing to the first item in the queue (either the item with the highest priority or the first entered into queue.
					// Assign this to temp2 for manipulation.
	info = temp->data;
	head_ptr = head_ptr->link; // Points head_ptr in the next item in the queue (either the item with the next highest priority or the next item inserted).
	--many_nodes;
	delete temp; // Frees the old memory so that it can be used again.
	return info; // returns value to function call.
}
