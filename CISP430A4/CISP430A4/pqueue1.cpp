/*
	Nathan Yarrison
	CISP 430
	Assignment 4
	10/20/2017
*/
// Implementation file for the pqueue1 header file.
#include <stdlib.h>
#include <cassert>
#include "pqueue1.h"

using namespace std;

typedef int Item;

PriorityQueue::PriorityQueue()
{
	// Initialize an empty queue.
	head_ptr = NULL; // Point head_ptr at NULL.
	many_nodes = 0; // Set amount of nodes to 0.
}

PriorityQueue::PriorityQueue(const PriorityQueue & source)
{
	many_nodes = source.many_nodes;         // Set the amount of nodes to the amount of nodes in the source queue.

	Node *temp, *precursor, *copycursor; // Declares a temporary node, a precursor, and a copycursor.
	temp = NULL;                    // temp will hold a temporar copy of the current node.
	precursor = NULL;                // Will point to the previous node in the queue.
	copycursor = NULL;               // will point to the current node to be copied.

	copycursor = source.head_ptr;           // point copycursor to the start of the queue.

	int numberOfCopiedNodes = 0;	// This is a variable that will hold how many nodes have been copied so far.
	while (numberOfCopiedNodes < many_nodes)               // While the number of copied nodes doesn't equal the total number of nodes, copy over nodes.
	{
		temp = new Node;               // Create a new node in temp.

		temp->data = copycursor->data;         // Copy data of copycursor to temp.
		temp->priority = copycursor->priority; // Copy priority of copycursor to temp.

		if (copycursor == source.head_ptr)      // if the copycursor is equivalent to the source head_ptr
		{
			head_ptr = temp;               // Set head_ptr of queue to the value of temp.
		}

		if (precursor != NULL)               // If precursor is not NULL
		{
			precursor->link = temp;            // Link node at precursor to the current node.
		}

		precursor = temp;              // precursor now points to the current node.
		copycursor = copycursor->link;          // Set copycursor to the next node in the queue.

		numberOfCopiedNodes++; // Keep count of the number of copied nodes.
	}
}

PriorityQueue::~PriorityQueue()
{

	if (many_nodes == 0) // Check if the number of nodes is 0.
	{
		// If it is, set head_ptr to NULL because the queue is empty.
		head_ptr = NULL;
		return;
	}

	// If the number of nodes is not 0, then the queue is not empty and needs to be emptied.
	while (head_ptr != NULL) // So, while the head_ptr does not point to NULL...
	{
		Node *temp = head_ptr; // Hold the value of head_ptr in a temp node.
		head_ptr = head_ptr->link; // Point head_ptr at the next node.
		delete temp; // Delete the original node, freeing the memory.
	}
	many_nodes = 0; // After while loop is exited, the queue should have been completely deleted so the number of nodes is now 0.
}

void PriorityQueue::operator=(const PriorityQueue & source)
{

	if (this == &source) // Checks if the two queue are already the same.
	{
		// If they are, don't do anything.
		return;
	}

	// If they are not, check if the source is empty and if the current head_ptr doesn't point to NULL.
	if ((source.head_ptr == NULL) && (head_ptr != NULL))
	{
		// If the source queue is empty, the current queue needs to be emptied.
		Node *temp; // Node to temporarily hold the value of head_ptr.
		while (head_ptr != NULL)
		{
			// While head_ptr doesn't point to NULL...
			temp = head_ptr; // Hold value of head_ptr in temp.
			head_ptr = head_ptr->link; // Point head_ptr at the next node.
			delete temp; // Delete the original node to free up the memory.
		}
	}
	
	// If the source queue is not empty...
	if (source.head_ptr != NULL)
	{
		many_nodes = source.many_nodes;         // Set the amount of nodes to the amount of nodes in the source queue.

		Node *temp, *precursor, *copycursor; // Declares a temporary node, a precursor, and a copycursor.
		temp = NULL;                    // temp will hold a temporar copy of the current node.
		precursor = NULL;                // Will point to the previous node in the queue.
		copycursor = NULL;               // will point to the current node to be copied.

		copycursor = source.head_ptr;           // point copycursor to the start of the queue.

		int numberOfCopiedNodes = 0;	// This is a variable that will hold how many nodes have been copied so far.
		while (numberOfCopiedNodes < many_nodes)               // While the number of copied nodes doesn't equal the total number of nodes, copy over nodes.
		{
			temp = new Node;               // Create a new node in temp.

			temp->data = copycursor->data;         // Copy data of copycursor to temp.
			temp->priority = copycursor->priority; // Copy priority of copycursor to temp.

			if (copycursor == source.head_ptr)      // if the copycursor is equivalent to the source head_ptr
			{
				head_ptr = temp;               // Set head_ptr of queue to the value of temp.
			}

			if (precursor != NULL)               // If precursor is not NULL
			{
				precursor->link = temp;            // Link node at precursor to the current node.
			}

			precursor = temp;              // precursor now points to the current node.
			copycursor = copycursor->link;          // Set copycursor to the next node in the queue.

			numberOfCopiedNodes++; // Keep count of the number of copied nodes.
		}
	}

	many_nodes = source.many_nodes; // Set the amount of nodes in the queue to the amount of nodes in the source.
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
		q = head_ptr; // points q to the head_ptr for use.
		while (q->link != NULL && q->link->priority >= priority)
		{
			// While q->link does not = NULL and the priority of q is greater than or equal to the given priority...
			q = q->link; // Point q at the next node.
		}
		temp->link = q->link; // Links temp to the next node in the q.
		q->link = temp; // Link q to the current node.
	}

	++many_nodes; // Keep track of how many nodes are in the queue.
}

Item PriorityQueue::get_front()
{
	// Gets the item at the front of the queue (the item with the highest priority), returns it to call, and removes it from the queue.

	// Assert that the size is greater than 0.
	assert(size() > 0);

	Node *temp; // Creates a node to temporarily hold the values of the nodes.
	Item info; // Creates an Item called info that will hold the value of data that will be returned to the call, which is the item at the front of the queue.

	temp = head_ptr; // head_ptr should be pointing to the first item in the queue (either the item with the highest priority or the first entered into queue.
					// Assign this to temp for manipulation.
	info = temp->data; // Store the value at temp->data in info because this is the item that will be returned to call.
	head_ptr = head_ptr->link; // Points head_ptr in the next item in the queue (either the item with the next highest priority or the next item inserted).
	--many_nodes; // Subtract one from the nuber of nodes to keep track of how many nodes are in the queue.
	delete temp; // Frees the old memory so that it can be used again.
	return info; // returns value to function call.
}
