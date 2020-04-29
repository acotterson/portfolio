/***********************************************************************
* Header:
*    LIST
* Summary:
*    This will contain just the List class, along with its ListIterator
*	 and the Node class that the list is made of
* Author
*    Alec Otterson
************************************************************************/
#pragma once

#include <iostream>
#include "bnode.h"
using namespace std;

template <class T>
class ListIterator;


/*******************************************
* List class
* create list of connected Nodes
******************************************/
template <class T>
class List
{
public:
	//default constructor
	List() : first(NULL), last(NULL), mySize(0) {}
	//copy constructor: copy the right hand side into a new list
	List(const List & rhs) throw (const char *);
	//destructor: destroy the list and free up the memory
	~List();
	//used to free memory recursively
	void freeData(BinaryNode<T>*& hNode);
	//set up the = operator to copy over a list
	List <T>& operator=(const List<T>& rhs) throw(const char *);
	//check if list is empty
	bool empty() { return mySize == 0; }
	//clear the data from the list and set the size to 0
	void clear();
	//get the size of the list
	int size() const { return mySize; }
	//push Node onto back of list
	void push_back(T newData) throw(const char *);
	//push node onto front of list
	void push_front(T newData) throw(const char *);
	//get data at front of list
	T & front() throw(const char *);
	//get data at back of list
	T & back() throw(const char *);
	//insert an item into the list somewhere and get iterator to new item
	ListIterator<T> insert(ListIterator<T> loc, T newData) throw(const char *);
	//remove desired Node from list
	void remove(ListIterator<T> loc) throw(const char *);
	//get iterator pointing to beginning of list
	ListIterator<T> begin();
	//get iterator pointing to end of list 9for reverse iteration)
	ListIterator<T> rbegin();
	//get NULL iterator (past end of list)
	ListIterator<T> end();
	//get NULL iterator (past front of list)
	ListIterator<T> rend();
	void addParents(int child, int father, int mother);
	void level();
private:
	//size of list
	int mySize;
	//pointer to first node of list
	BinaryNode <T>* first;
	//pointer to last node of list
	BinaryNode <T>* last;
};

/*******************************************
* Copy constructor
* create copy of rhs list for lhs
******************************************/
template<class T>
List<T>::List(const List <T> & rhs) throw(const char *)
{
	//make three NULL Nodes
	BinaryNode <T> *newHead = NULL;
	BinaryNode <T> *preNode = NULL;
	BinaryNode <T> *nNode = NULL;

	//if rhs is empty, skip all this
	if (rhs.first != NULL)
	{
		//do all this if rhs has something to copy
		//try to allocatea node for the lhs head
		try
		{
			newHead = new BinaryNode <T>(rhs.first->data);	//set the newHead node data equal to the data in first node in rhs
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: unable to allocate a new node for a list";
		}

		//try to allocate node for iterative preNode of lhs
		try
		{
			preNode = new BinaryNode <T>();
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: unable to allocate a new node for a list";
		}
		//preNode starts out pointing to same node as newHead
		preNode = newHead;
		//iterative current node pointer starts at first node of rhs
		BinaryNode <T>* current = rhs.first;

		//copy stuff over as long as there are more rhs nodes to copy
		while (current->pNext != NULL)
		{
			//icrement rhs iterator
			current = current->pNext;
			//create new node and copy data from current into it
			try
			{
				nNode = new BinaryNode <T>(current->data);
			}
			catch (std::bad_alloc)
			{
				throw "ERROR: unable to allocate a new node for a list";
			}
			preNode->pNext = nNode;		//preNode points forward to nNode
			nNode->pPrev = preNode;		//nNode points back to preNode
			preNode = nNode;			//preNode pointer moves forward, now pointing to nNode
		}
	}

	this->first = newHead;	//first node is at newHead address
	this->last = preNode;	//last node is at preNode address
	this->mySize = rhs.mySize;	//size of lhs is same as size of rhs
}

/*******************************************
* destructor
* destroy all list nodes/free up memory
******************************************/
template<class T>
List<T>::~List()		//not sure if way to call destructor recursively, so I used a separate function
{
	//use freeData to do it recursively
	freeData(first);
}

/*******************************************
* freeData
* delete nodes/free memory
******************************************/
template <class T>
void List<T>::freeData(BinaryNode <T>* & hNode)
{
	//if the node pointer isn't already NULL, do this
	if (hNode != NULL)
	{
		//as long as there is a subsequent node, call this function (freeData) with the next node
		while (hNode->pNext != NULL)
		{
			freeData(hNode->pNext);
		}

		//delete the current Node
		delete hNode;
		//set the current node to NULL
		hNode = NULL;
	}
}

/*******************************************
* = operator
* allow copying lists with = sign
******************************************/
template<class T>
List <T>& List<T>::operator=(const List<T>& rhs) throw(const char *)
{
	//do this if the rhs has something in it
	if (rhs.mySize != 0)
	{
		//create a new node for the first list item of lhs if a lhs list doesn't aready exist
		if (this->mySize == 0)
		{
			try
			{
				this->first = new BinaryNode <T>(rhs.first->data);
			}
			catch (std::bad_alloc)
			{
				throw "ERROR: unable to allocate a new node for a list";
			}
		}
		//otherwise copy the data from the first rhs node to the first lhs node
		else
			this->first->data = rhs.first->data;

		//set up two node pointers in case they are needed
		BinaryNode <T> *preNode = NULL;
		BinaryNode <T> *nNode = NULL;

		//set iterative "preNode" to point to the first item in lhs list
		preNode = this->first;
		//make iterative "current" point to first item in rhs list
		BinaryNode <T>* current = rhs.first;

		//run through this code as long as there is stuff to copy from rhs
		while (current->pNext != NULL)
		{
			//move current pointer to next node
			current = current->pNext;

			//if there are still existing nodes in lhs, simply copy rhs node data into them
			if (preNode->pNext != NULL)
			{
				preNode = preNode->pNext;
				preNode->data = current->data;
			}
			//if lhs is out of existing nodes, create new ones to copy rhs node data into (same as copy constructor)
			else
			{
				try
				{
					nNode = new BinaryNode <T>(current->data);
				}
				catch (std::bad_alloc)
				{
					throw "ERROR: unable to allocate a new node for a list";
				}
				preNode->pNext = nNode;
				nNode->pPrev = preNode;
				preNode = nNode;
			}
		}
		//lhs last points to preNode
		this->last = preNode;
		//lhs size same as rhs size
		this->mySize = rhs.mySize;
		// if the original lhs list was longer than rhs list, delete extra nodes starting with the node following last
		if (preNode->pNext != NULL)
			freeData(preNode->pNext);
	}
	//if the rhs list was empty, make lhs an empty list as well
	else
	{
		if (this->first != NULL)	//delete all existing nodes in lhs
			freeData(this->first);
		this->first = NULL;
		this->last = NULL;
		this->mySize = 0;
	}

	//return pointer to this
	return *this;
}

/*******************************************
* clear
* clear the specified list
******************************************/
template<class T>
void List<T>::clear()
{
	freeData(first);	//delete all the nodes
	mySize = 0;			//set size to 0
	first = NULL;		//set both pointers to NULL
	last = NULL;
}

/*******************************************
* push_back
* add item to end of list
******************************************/
template<class T>
void List<T>::push_back(T newData) throw(const char *)
{
	//create NULL newNode pointer and then point it to a new node created with passed in data
	BinaryNode <T>* newNode = NULL;
	try
	{
		newNode = new BinaryNode<T>(newData);
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a new node for a list";
	}

	//if the list is currently empty, make the first and last pointers point to the new node
	if (empty())
	{
		this->last = newNode;
		this->first = newNode;
	}
	//if the list has stuff
	else
	{
		this->last->pNext = newNode;	//makethe original last node point forward to the new node
		newNode->pPrev = this->last;	//make the new node point backward to the original last node
		this->last = newNode;			//make last pointer point to newNode
	}
	//increase the size of the list
	mySize++;
}

/*******************************************
* push_front
* add node to front of list
* *****************************************/
template<class T>
void List<T>::push_front(T newData) throw(const char *)
{
	//same as push_back, but at front of list
	BinaryNode <T>* newNode = NULL;
	try
	{
		newNode = new BinaryNode<T>(newData);
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a new node for a list";
	}
	if (empty())
	{
		this->last = newNode;
		this->first = newNode;
	}
	else
	{
		this->first->pPrev = newNode;
		newNode->pNext = this->first;
		this->first = newNode;
	}
	mySize++;
}

/*******************************************
* front
* get value from front of list
******************************************/
template<class T>
T & List<T>::front() throw(const char *)
{
	//error message if list is empty
	if (empty())
		throw "ERROR: unable to access data from an empty list";
	//return data inside first node
	else
		return first->data;
}

/*******************************************
* back
* get value from back of list
******************************************/
template<class T>
T & List<T>::back() throw(const char *)
{
	//same as front, but with back node
	if (empty())
		throw "ERROR: unable to access data from an empty list";
	else
		return last->data;
}

/*******************************************
* insert
* insert new data (node) into list
******************************************/
template<class T>
ListIterator<T> List<T>::insert(ListIterator<T> loc, T newData) throw(const char *)
{
	//create the new pointer to a node and point it to a new node created with the passed in data
	BinaryNode<T> * tmp = NULL;
	try
	{
		tmp = new BinaryNode<T>(newData);
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a new node for a list";
	}

	if (first == NULL)          // insert into an empty list
	{
		this->first = tmp;
		this->last = tmp;
		loc.p = this->first;
	}
	else if (loc == end())     // insert at end of list
	{
		this->last->pNext = tmp;
		tmp->pPrev = this->last;
		this->last = tmp;
		loc.p = this->last;
	}
	else
	{
		tmp->pNext = loc.p;                   // insert at beginning or middle
		tmp->pPrev = loc.p->pPrev;
		loc.p->pPrev = tmp;
		if (loc.p == this->first)
			this->first = tmp;                        // insert at beginning 
		else
			tmp->pPrev->pNext = tmp;					// insert in middle
		loc--;
	}
	
	//return iterator pointing to inserted node
	return loc;
}

///***********************************************
//* INSERTION SORT
//* Sort the items in the array
//**********************************************/
//template <class T>
//void sortInsertion(T newData)
//{
//	//create the new pointer to a node and point it to a new node created with the passed in data
//	BinaryNode<T> * tmp = NULL;
//	try
//	{
//		tmp = new BinaryNode<T>(newData);
//	}
//	catch (std::bad_alloc)
//	{
//		throw "ERROR: unable to allocate a new node for a list";
//	}
//
//	if (first == NULL)          // insert into an empty list
//	{
//		this->first = tmp;
//		this->last = tmp;
//	}
//
//	//as long as the array still has data, do this
//		BinaryNode <T>* newNode = this->first;		//make newNode pointer point to hNode
//		if (first->data > newData)		//if the data in the first node is larger than the data in the current array element
//			this->push_front(newData);	//insert the element as the head node
//		else						//do this for all non-head elements
//		{
//			while (newNode->data < newData)	//while the data in the newNode location is less thatn the current array element
//			{
//				if (newNode->pNext == NULL)		//if we are on the last node
//					this->push_back(newData);	//insert the element after the last node
//				else if (newNode->pNext->data > newData)	//if the data in the next node is greater than the current element
//					insert(array[i], newNode);				//insert the element after the current node (a little redundant I suppose, but clear)
//				else				//if the data at both this and the next node are smaller than the current element
//				{
//					newNode = newNode->pNext;	//move the newNode pointer to point to the next node
//				}
//			}
//		}
//	}
//
//	for (int i = 0; i < num; i++)	//copy dat from the series of nodes back into the array in order
//	{
//		array[i] = hNode->data;
//		if (hNode->pNext != NULL)
//			hNode = hNode->pNext;
//	}
//}

/*******************************************
* remove
* remove a data (node) from the list
******************************************/
template<class T>
void List<T>::remove(ListIterator<T> loc) throw(const char *)
{
	//error if iterators point off end of list
	if (loc == end() || loc == rend())
		throw "ERROR: unable to remove from an invalid location in a list";
	//make first and last point to NULL if list started with only one item
	else if (mySize == 1)
	{
		this->last = NULL;
		this->first = NULL;
	}
	//remove item from front of list and reset pointers accordingly
	else if (loc.p == this->first)
	{
		this->first = loc.p->pNext;
		this->first->pPrev = NULL;
	}
	//remove item from end of list and reset pointers accordingly
	else if (loc.p == this->last)
	{
		this->last = loc.p->pPrev;
		this->last->pNext = NULL;
	}
	//remove item from middle of list and reset pointers accordingly
	else
	{
		loc.p->pNext->pPrev = loc.p->pPrev;
		loc.p->pPrev->pNext = loc.p->pNext;
	}
	
	//loc.p is node we removed, now detached from list; free the memory now
	delete loc.p;
	//decrease list size to account for removed node
	mySize--;
}

/*******************************************
* begin
* get iteratro pointing to front of list
******************************************/
template<class T>
ListIterator<T> List<T>::begin()
{
	//NULL pointer if list is empty, pointer to first item if not
	if (empty())
		return ListIterator<T>();
	else
		return ListIterator<T>(this->first);
}

/*******************************************
* rbegin
* get iterator to end of list (for reverse iteration)
******************************************/
template<class T>
ListIterator<T> List<T>::rbegin()
{
	//NULL pointer if empty list, otherwise pointer to last item
	if (empty())
		return ListIterator<T>();
	else
		return ListIterator<T>(this->last);
}

/*******************************************
* end
* get iterator to off the end of list
******************************************/
template<class T>
ListIterator<T> List<T>::end()
{
	//iterator will just be NULL
	return ListIterator<T>();
}

/*******************************************
* rend
* get iterator to off the end of list
******************************************/
template<class T>
ListIterator<T> List<T>::rend()
{
	//iterator will just be NULL
	return ListIterator<T>();

}

template<class T>
void List<T>::addParents(int child, int father, int mother)
{
	ListIterator<T> it = this->begin();
	for (it; it != this->end(); ++it)
	{
		if (*it == child)
		{
			break;
		}
	}
	if (father != 0)
	{
		for (ListIterator<T> fIt = it; fIt != this->end(); ++fIt)
		{
			if (*fIt == father)
			{				
				(it.getNode())->addFather(fIt.getNode());
				break;
			}
		}
	}
	if (mother != 0)
	{
		for (ListIterator<T> mIt = it; mIt != this->end(); ++mIt)
		{
			if (*mIt == mother)
			{
				(it.getNode())->addMother(mIt.getNode());
				break;
			}
		}
	}
}

template <class T>
void List <T> ::level()
{
	const int MAX = 100;
	BinaryNode <T> *queue[MAX];
	BinaryNode <T> *temp;
	int front = 0;
	int back = 0;

	ListIterator<T> it = this->begin();
	for (it; it != this->end(); ++it)
	{
		if (*it == 1)
			break;
	}
	queue[back++] = it.getNode();
	int gen = 1;

	while (front != back)
	{
		temp = queue[front];
		front = (front + 1) % MAX;
		if (temp != NULL)
		{
			// visit
			cout.width(4);
			cout << temp->data;
			if (back + 1 != front)
				cout << endl;
			// end Visit        
			queue[back] = temp->pFather;
			back = (back + 1) % MAX;
			queue[back] = temp->pMother;
			back = (back + 1) % MAX;

		}
	}
}

//ListIterator class definition (to create iterators to easily go through lists)
template <class T>
class ListIterator
{
public:
	// default constructor
	ListIterator() : p(NULL) {}

	// initialize to direct p to some item
	ListIterator(BinaryNode <T> * p) : p(p) {}

	//=operator overload
	ListIterator & operator = (const ListIterator & rhs)
	{
		//list lhs pointer to be equal to rhs pointer
		this->p = rhs.p;
		//return lhs iterator object
		return *this;
	}

	//==operator overload
	bool operator == (const ListIterator & rhs) const
	{
		//return true if the lhs and rhs pointers are equal, false otherwise
		return this->p == rhs.p;
	}

	// not equals operator
	bool operator != (const ListIterator & rhs) const
	{
		//return false if the lhs and rhs pointers are equal, true otherwise
		return this->p != rhs.p;
	}

	// dereference operator
	T & operator * ()
	{
		//return the element located at the iterator location
		return this->p->data;
	}

	// prefix increment
	ListIterator <T> & operator ++ ()
	{
		//move the iterator pointer forward one address location
		p = p->pNext;
		//return the lhs iterator object
		return *this;
	}

	// postfix increment
	ListIterator <T> operator++(int postfix)
	{
		//make temporary iterator object at current element
		ListIterator tmp(*this);
		//move iterator pointer forward one address location
		p = p->pNext;
		//return the temporary iterator object
		return tmp;
	}

	// prefix decrement
	ListIterator <T> & operator -- ()
	{
		//move the iterator pointer forward one address location
		p = p->pPrev;
		//return the lhs iterator object
		return *this;
	}

	// postfix decrement
	ListIterator <T> operator--(int postfix)
	{
		//make temporary iterator object at current element
		ListIterator tmp(*this);
		//move iterator pointer forward one address location
		p = p->pPrev;
		//return the temporary iterator object
		return tmp;
	}
	
	//make insert and remove functions friends of ListIterator so that data at iterator location may be accessed
	friend ListIterator<T> List<T>::insert(ListIterator<T> loc, T newData) throw(const char *);
	friend void List<T>::remove(ListIterator<T> loc) throw(const char *);
	friend void List<T>::addParents(int child, int father, int mother) throw(const char *);
	friend void List <T> ::level();
private:
	// get the node pointer
	BinaryNode <T> * getNode() { return p; }
	//pointer to element at iterator location
	BinaryNode<T>* p;
};