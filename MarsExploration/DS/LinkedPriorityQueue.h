#pragma once
#include "Node.h"
#include "PriorityQueueADT.h"
using namespace std;


template <typename T>
class LinkedPriorityQueue :public PriorityQueueADT<T>
{
private:

	Node<T>* backPtr;
	Node<T>* frontPtr;
public:
	LinkedPriorityQueue();
	bool isEmpty() const;
	bool add(const T& newEntry, double priority);
	bool remove(T& frntEntry);
	bool peek(T& frntEntry)  const;
	~LinkedPriorityQueue();

	//copy constructor
	LinkedPriorityQueue(const LinkedPriorityQueue<T>& LQ);
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
LinkedPriorityQueue<T>::LinkedPriorityQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this PriorityQueue is empty.

Input: None.
Output: True if the PriorityQueue is empty; otherwise false.
*/
template <typename T>
bool LinkedPriorityQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:add
Adds newEntry at the correct position of this PriorityQueue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedPriorityQueue<T>::add(const T& newEntry, double priority)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	newNodePtr->setpriority(priority);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
	{
		frontPtr = newNodePtr; // The PriorityQueue is empty
		backPtr = newNodePtr;
	}
	else if (newNodePtr->priority > frontPtr->priority)
	{
		newNodePtr->setNext(frontPtr);
		frontPtr = newNodePtr;
	}
	else
	{
		Node<T>* P = frontPtr;
		Node<T>* B = P->getNext();
		bool z = false;
		while (B && !z)
		{
			if (newNodePtr->priority > B->priority)
			{
				newNodePtr->setNext(B);
				P->setNext(newNodePtr);
				z = true;
			}

			P = P->getNext();
			B = B->getNext();
		}
		if (z == false)
		{
			P->setNext(newNodePtr);
		}
	}
	return true;
} // end add


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: remove
Removes the front of this PriorityQueue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedPriorityQueue<T>::remove(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// PriorityQueue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the Priorityqueue
		backPtr = nullptr;

	// Free memory reserved for the removed node
	delete nodeToDeletePtr;

	return true;

}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: peek
copies the front of this PriorityQueue to the passed param. The operation does not modify the PriorityQueue.

Input: None.
Output: The front of the PriorityQueue.
*/
template <typename T>
bool LinkedPriorityQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////
/*
Function: destructor
removes all nodes from the PriorityQueue by dequeuing them
*/
template <typename T>
LinkedPriorityQueue<T>::~LinkedPriorityQueue()
{
	T temp;

	//Free (Dequeue) all nodes in the queue
	while (remove(temp));
}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: Copy constructor
To avoid shallow copy,
copy constructor is provided

Input: LinkedQueue<T>: The PriorityQueue to be copied
Output: none
*/

template <typename T>
LinkedPriorityQueue<T>::LinkedPriorityQueue(const LinkedPriorityQueue<T>& LQ)
{
	Node<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	Node<T>* ptr = new Node<T>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}

}

