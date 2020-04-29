/*********************************************************************************************
* Header:
*    BNODE
* Summary:
*    This will contain just the bnode class
* Author
*    Alec Otterson
**********************************************************************************************/
#pragma once

#include <iostream> 
#include <cassert>
using namespace std;
/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BinaryNode
{
public:
	//default constructor to create empty, disconnected BinaryNode
	BinaryNode() : pFather(NULL), pMother(NULL), pChild(NULL), pNext(NULL), pPrev(NULL) {}
	//non-default constructor to create disconnected BinaryNode with passed in data
	BinaryNode(T newData) : data(newData), pFather(NULL), pMother(NULL), pChild(NULL), pNext(NULL), pPrev(NULL) {}

	// return size (i.e. number of nodes in tree)
	int size() const
	{
		return 1 +
			(pFather == NULL ? 0 : pFather->size()) +
			(pMother == NULL ? 0 : pMother->size());
	}

	// add a node to the left/right
	void addFather(BinaryNode <T> * pNode);
	void addMother(BinaryNode <T> * pNode);

	// create a node and add it to the left/right
	void addFather(const T & t) throw (const char *);
	void addMother(const T & t) throw (const char *);



	// since no validation is done, everything is public
	BinaryNode <T> * pFather;
	BinaryNode <T> * pMother;
	BinaryNode <T> * pChild;
	BinaryNode <T> * pNext;
	BinaryNode <T> * pPrev;
	T data;
};

/******************************************************************************************************
*addFather(node input)
*add given node as left child
******************************************************************************************************/
template<class T>
void BinaryNode<T>::addFather(BinaryNode<T>* pNode)
{
	//set lhs pFather to point to the pNode
	this->pFather = pNode;
	//set the pNode pChild to point to the current node
	if (pNode != NULL)
		pNode->pChild = this;
}

/******************************************************************************************************
*addMother(node input)
*add given node as right child
******************************************************************************************************/
template<class T>
void BinaryNode<T>::addMother(BinaryNode<T>* pNode)
{
	//set lhs pMother to point to the pNode
	this->pMother = pNode;
	//set the pNode pChild to point to the current node
	if (pNode != NULL)
		pNode->pChild = this;
}

/******************************************************************************************************
*addFather(data input)
*add left child node with given data
******************************************************************************************************/
template<class T>
void BinaryNode<T>::addFather(const T & t) throw(const char *)
{
	//try to create a new node holding the passed data
	BinaryNode <T>* newNode;
	try
	{
		newNode = new BinaryNode <T>(t);
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a node";
	}
	//set lhs pFather to point to the newNode
	this->pFather = newNode;
	//set the newNode pChild to point to the current node
	newNode->pChild = this;
}

/******************************************************************************************************
*addMother(data input)
*add right child node with given data
******************************************************************************************************/
template<class T>
void BinaryNode<T>::addMother(const T & t) throw(const char *)
{
	//try to create a new node holding the passed data
	BinaryNode <T>* newNode;
	try
	{
		newNode = new BinaryNode <T>(t);
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a node";
	}
	//set lhs pMother to point to the newNode
	this->pMother = newNode;
	//set the newNode pChild to point to the current node
	newNode->pChild = this;
}

/******************************************************************************************************
*vdeleteBinaryTree
*delete the tree and free the data from the given node on down
******************************************************************************************************/
template <class T>
void deleteBinaryTree(BinaryNode <T>* currentNode)
{
	////if the node pointer isn't already NULL, do this
	if (currentNode != NULL)
	{
		//as long as there is a subsequent node, call this function (freeData) with the next node
		while (currentNode->pFather != NULL)
		{
			deleteBinaryTree(currentNode->pFather);
		}
		while (currentNode->pMother != NULL)
		{
			deleteBinaryTree(currentNode->pMother);
		}
		if (currentNode->pChild != NULL)	//head node doesn't have a parent
		{
			//set the parent's pointer to the current node to NULL
			if (currentNode->pChild->pFather != NULL && currentNode->pChild->pFather == currentNode)
				currentNode->pChild->pFather = NULL;	
			else if (currentNode->pChild->pMother != NULL && currentNode->pChild->pMother == currentNode)
				currentNode->pChild->pMother = NULL;
		}
		//delete the current Node
		delete currentNode;
		//set the current node to NULL
		currentNode = NULL;
	}
}

/******************************************************************************************************
*<< operator overload
*recursively output the data conatined in all the linked binary nodes
******************************************************************************************************/
template <class T>
ostream & operator<<(ostream &out, const BinaryNode <T>* currentNode)
{
	if (currentNode != NULL)
	{
		//call this function with the left child
		out << currentNode->pFather;
		//output the current data
		out << currentNode->data << ' ';
		//call this function with the right child
		out << currentNode->pMother;
	}
	else
		return out;
}

