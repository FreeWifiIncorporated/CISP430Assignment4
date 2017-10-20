#include <stdlib.h>
#include <cassert>
#include "pqueue1.h"

typedef int Item;

PriorityQueue::PriorityQueue()
{
	head_ptr = NULL;
	many_nodes = 0;
}

PriorityQueue::PriorityQueue(const PriorityQueue & source)
{
	head_ptr = source.head_ptr;
	many_nodes = source.many_nodes;
}

PriorityQueue::~PriorityQueue()
{
	many_nodes = 0;
}

void PriorityQueue::operator=(const PriorityQueue & source)
{
}

void PriorityQueue::insert(const Item & entry, unsigned int priority)
{
	Node* n; // Pointer to a specific node in linked list.
	n->priority = priority;
	if (head_ptr == NULL) // Checks if head_ptr is equal to NULL.
	{
		// If it is, then there are no items in the queue and the new entry must be inserted at the front but keep priority.
		head_ptr = n;
	}
	else // Else, there is an item in the queue and priority must be checked, greater priority is first in queue.
	{
		Node* temp = head_ptr;
		if (n->priority > temp->priority)
		{
			head_ptr->link = n;
		}
		else
	}
}

Item PriorityQueue::get_front()
{
	assert(!size() < 0);
	return head_ptr->data;
}
