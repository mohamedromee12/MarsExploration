#pragma once
template < typename T>
class Node
{
private:
	T item; // A data item

	Node<T>* next; // Pointer to next node
public:
	double priority;
	Node();
	Node(const T& r_Item);
	Node(const T& r_Item, float p);
	Node(const T& r_Item, Node<T>* nextNodePtr);
	void setItem(const T& r_Item);
	void setpriority(double p);
	void setNext(Node<T>* nextNodePtr);
	T getItem() const;
	double getpriority() const;
	Node<T>* getNext() const;
}; // end Node


template < typename T>
Node<T>::Node()
{
	next = nullptr;
	priority = 0;
}

template < typename T>
Node<T>::Node(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
	priority = 0;
}
template < typename T>
Node<T>::Node(const T& r_Item, float p)
{
	item = r_Item;
	priority = p;
	next = nullptr;
}

template < typename T>
Node<T>::Node(const T& r_Item, Node<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
void Node<T>::setItem(const T& r_Item)
{
	item = r_Item;
}
template < typename T>
void Node<T>::setpriority(double p)
{
	priority = p;
}
template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
T Node<T>::getItem() const
{
	return item;
}
template < typename T>
double Node<T>::getpriority() const
{
	return priority;
}
template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
}