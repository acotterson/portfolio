/***********************************************************************
 * Component:
 *    Binary Search Tree (BST)
 * Author: Helfrich
 *    Modified by Scott Ercanbrack - removed most of the the BST class functions,       
 *                                   but father BST Iterator class.
 * Summary:
 *    Create a binary search tree
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include "bnode.h"    // for BinaryNode
#include "stack.h"    // for Stack
#include "person.h"

// forward declaration for the BST iterator
template <class T>
class BSTIterator;

/*****************************************************************
 * BINARY SEARCH TREE
 * Create a Binary Search Tree
 *****************************************************************/
template <class T>
class BST
{
  public:
   // constructor
  BST() : root(NULL) {};
   
   // copy constructor
   BST(const BST & rhs);
   
   ~BST();
   
   int  size() const { return empty() ? 0 : root->size(); }   // BinaryNode class needs a size function
   
   
   // determine if the tree is empty
   bool empty() const
   {
      return this->root == NULL;
   }
   
   // remove all the nodes from the tree.  Makes an empty tree.
   void clear()
   {
      deleteBinaryTree(this->root);
      this->root = NULL;
   }
   
   // overloaded assignment operator
   BST & operator = (const BST & rhs) throw (const char *);
   
   // insert an item
   void insert(const T & t, int id = 0, int type = 0) throw (const char *);
   
   // remove an item
   void remove(BSTIterator <T> & it);
   
   // find a given item
   BSTIterator <T> find(const T & t);
   
   // the usual iterator stuff
   BSTIterator <T> begin() const;
   BSTIterator <T> end() const { return BSTIterator <T>(NULL); }
   BSTIterator <T> rbegin() const;
   BSTIterator <T> rend() const { return BSTIterator <T>(NULL); }

   void level();
   
   

  private:
   
   BinaryNode <T> * root;
   //recursive copy function
   void reCopy(BinaryNode <T>* copy, BinaryNode <T>* toCopy);
};

/*********************************************************
 * copy constructor
 **********************************************************/
template <class T>
BST<T>::BST(const BST &rhs)
{
   //set root to null and then call = operator
   this->root = NULL;
   *this = rhs;
}

/*****************************************************
 * Destructor
 *******************************************************/
template <class T>
BST<T>::~BST()
{
   //check if rhs is empty
   if (this->root != NULL)
   {
      //use the deletebinarytree function and set root to null
      deleteBinaryTree(this->root);
      this->root = NULL;
   }
}


/*****************************************************
 * = operator overload
 *******************************************************/
template <class T>
BST <T>& BST <T>::operator = (const BST & rhs) throw (const char *)
{
   //if the lhs has stuff in it, clear it out
   if (this->root != NULL)
      this->clear();
   //see if rhs is null
   if(rhs.root != NULL)
   {
      //create the root node
      BinaryNode <T>* newNode;
      try
      {
         newNode = new BinaryNode <T>(rhs.root->data);
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a node";
      }
      this->root = newNode;
      //use the recursive copy function with lhs and rhs roots as parameters
      reCopy(this->root, rhs.root);
   }
   //if the rhs was empty, just set the lhs root to null
   else
   {
      this->root = NULL;
   }
   //return the copied BST
   return *this;
}
   
/*****************************************************
 * BST :: BEGIN
 * Return the first node (father-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> ::begin() const
{
   Stack < BinaryNode <T> * > nodes;
   
   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pFather)
      nodes.push(nodes.top()->pFather);
   
   return BSTIterator<T>(nodes);
}

/*****************************************************
 * BST :: RBEGIN
 * Return the last node (mother-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> ::rbegin() const
{
   Stack < BinaryNode <T> * > nodes;
   
   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pMother)
      nodes.push(nodes.top()->pMother);
   
   return BSTIterator<T>(nodes);
}

/*****************************************************
 * BST :: INSERT
 * Insert a node at a given location in the tree
 ****************************************************/
template <class T>
void BST <T> ::insert(const T & t, int id, int type) throw (const char *)
{
   //see if were working with an empty tree and just need to add a root
   if (this->empty())
   {
      BinaryNode <T>* newNode;
      try
      {
         newNode = new BinaryNode <T>(t);
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a node";
      }
      this->root = newNode;
      return;
   }
   //make a pointer to the root
   BinaryNode <T>* tmp;
   tmp = this->root;
   //do this while there's stuff to check
   while (tmp != NULL)
   {
      //do this if t is less than the node data
      if ( type == 1)
      {
         //if there is no father node, add t there
         if (tmp->data == id)
         {
            tmp->addFather(t);
            tmp = NULL;
         }
         //otherwise move the pointer to the father
         else
            tmp=tmp->pFather;
      }
      //same thing on the mother if t is greater than the node data
      else if (type == 2)
      {
         if (tmp->data == id)
         {
            tmp->addMother(t);
            
            tmp = NULL;
         }
         else
            tmp=tmp->pMother;
      }
   }
}

/*************************************************
 * BST :: REMOVE
 * Remove a given node as specified by the iterator
 ************************************************/
template <class T>
void BST <T> ::remove(BSTIterator <T> & it)
{
   //dont do this if the iterator points to nothing
   if (it != NULL)
   {
      //get the node the iterator is pointing to
      BinaryNode <T>* targetNode = it.getNode();
      //2 child case
      if (targetNode->pFather != NULL && targetNode->pMother != NULL)
      {
         //move the pointer to the node to the mother 
         BinaryNode <T>* successor = targetNode->pMother;
         //move the pointer to the fathermost node
         while (successor->pFather != NULL)
         {
            successor = successor->pFather;
         }
         //copy the data over to the target node
         targetNode->data = successor->data;
         //set the connection pointers depending on where to node ti be deleted is
         if (targetNode->pMother == successor)
         {
            targetNode->pMother = successor->pMother;
         }
         else
         {
            successor->pChild->pFather = successor->pMother;
         }
         //check if dealing with root
         if (successor->pMother != NULL)
            successor->pMother->pChild = successor->pChild;
         //we want to delete the successor now, so make that the target node
         targetNode = successor;
      }
      //case for one child
      else if (targetNode->pFather != NULL || targetNode->pMother != NULL)
      {
         //set a pointer to the one child
         BinaryNode <T>* child = targetNode->pFather;
         if (targetNode->pFather == NULL)
            child = targetNode->pMother;
         //case for root deletion
         if (targetNode->pChild == NULL)
         {
            this->root = child;
            child->pChild = NULL;
         }
         //otherwise set the node pointers ti the mother places
         else if (targetNode->pChild->pFather == targetNode)
         {
            targetNode->pChild->pFather = child;
            child->pChild = targetNode->pChild;
         }
         else
         {
            targetNode->pChild->pMother = child;
            child->pChild = targetNode->pChild;
         }
      }
      //case for no children
      else
      {
         //make sure any childs have pointers set mother
         if (targetNode->pChild != NULL)
         {
            if (targetNode->pChild->pFather == targetNode)
               targetNode->pChild->pFather = NULL;
            else
               targetNode->pChild->pMother = NULL;
         }
      }
      //delete the target node
      delete targetNode;
      targetNode = NULL; 
   }
}

/****************************************************
 * BST :: FIND
 * Return the node corresponding to a given value
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> ::find(const T & t)
{
   //make a pointer ti the root
   BinaryNode <T>* tmp = this->root;
   //do this while the pointer is pointing to a node
   while (tmp != NULL)
   {
      //move pointer based on if t is greater than or less than current data
      if (t < tmp->data)
         tmp = tmp->pFather;
      else if (t > tmp->data)
         tmp = tmp->pMother;
      else
         return BSTIterator <T>(tmp); //return iterator to here if we find t
   }
   return BSTIterator <T>(NULL); //return null iterstor if data not found
}

/****************************************************
 * BST :: ReCopy
 * Copy the rhd to the lhs recursively
 ****************************************************/
template <class T>
void BST <T> ::reCopy(BinaryNode <T>* copy,BinaryNode <T>* toCopy)
{
   //if rhs father has a node, copy it to lhs father
   if (toCopy->pFather != NULL)
   {
      copy->addFather(toCopy->pFather->data);
      reCopy(copy->pFather, toCopy->pFather); //recall this function on father node
   }
   //same thing on nodes to the mother
   if (toCopy->pMother != NULL)
   {
      copy->addMother(toCopy->pMother->data);
      reCopy(copy->pMother, toCopy->pMother);
   }
}


template <class T>
void BST <T> ::level()
{
	const int MAX = 100;
	BinaryNode <T> *queue[MAX];
	BinaryNode <T> *temp;
	int front = 0;
	int back = 0;

	queue[back++] = this->root;

	while (front != back)
	{
		temp = queue[front];
		front = (front + 1) % MAX;
		if (temp != NULL)
		{
			// visit
			cout.width(4);
			cout << temp->data << " ";
			// end Visit        
			queue[back] = temp->pFather;
			back = (back + 1) % MAX;
			queue[back] = temp->pMother;
			back = (back + 1) % MAX;

		}
	}
}
/**********************************************************
 * BINARY SEARCH TREE ITERATOR
 * Forward and reverse iterator through a BST
 *********************************************************/
template <class T>
class BSTIterator
{
  public:
   // constructors
   BSTIterator(BinaryNode <T> * p = NULL) { nodes.push(p); }
   BSTIterator(Stack <BinaryNode <T> *> & s) { nodes = s; }
   BSTIterator(const BSTIterator <T> & rhs) { nodes = rhs.nodes; }
   
   // assignment
   BSTIterator <T> & operator = (const BSTIterator <T> & rhs)
      {
         // need an assignment operator for the Stack class.
         nodes = rhs.nodes;
         return *this;
      }
   
   // compare
   bool operator == (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node
      return rhs.nodes.const_top() == nodes.const_top();
   }
   bool operator != (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node
      return rhs.nodes.const_top() != nodes.const_top();
   }
   
   // de-reference data. Cannot change because it will invalidate the BST
   T & operator * ()
   {
      return nodes.top()->data;
   }
   
   // iterators
   BSTIterator <T> & operator ++ ();
   BSTIterator <T>   operator ++ (int postfix)
   {
      BSTIterator <T> itReturn = *this;
      ++(*this);
      return itReturn;
   }
   BSTIterator <T> & operator -- ();
   BSTIterator <T>   operator -- (int postfix)
   {
      BSTIterator <T> itReturn = *this;
      --(*this);
      return itReturn;
   }
   
   // must give friend status to remove so it can call getNode() from it
   friend void BST <T> ::remove(BSTIterator <T> & it);
   
  private:
   
   // get the node pointer
   BinaryNode <T> * getNode() { return nodes.top(); }
   
   // the stack of nodes
   Stack < BinaryNode <T> * > nodes;
};


/**************************************************
 * BST ITERATOR :: INCREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator ++ ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;
   
   // if there is a mother node, take it
   if (nodes.top()->pMother != NULL)
   {
      nodes.push(nodes.top()->pMother);
      
      // there might be more father-most children
      while (nodes.top()->pFather)
         nodes.push(nodes.top()->pFather);
      return *this;
   }
   
   // there are no mother children, the father are done
   assert(nodes.top()->pMother == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();
   
   // if the child is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;
   
   // if we are the father-child, got to the child.
   if (pSave == nodes.top()->pFather)
      return *this;
   
   // we are the mother-child, go up as long as we are the mother child!
   while (nodes.top() != NULL && pSave == nodes.top()->pMother)
   {
      pSave = nodes.top();
      nodes.pop();
   }
   
   return *this;
}

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator -- ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;
   
   // if there is a father node, take it
   if (nodes.top()->pFather != NULL)
   {
      nodes.push(nodes.top()->pFather);
      
      // there might be more mother-most children
      while (nodes.top()->pMother)
         nodes.push(nodes.top()->pMother);
      return *this;
   }
   
   // there are no father children, the mother are done
   assert(nodes.top()->pFather == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();
   
   // if the child is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;
   
   // if we are the mother-child, got to the child.
   if (pSave == nodes.top()->pMother)
      return *this;
   
   // we are the father-child, go up as long as we are the father child!
   while (nodes.top() != NULL && pSave == nodes.top()->pFather)
   {
      pSave = nodes.top();
      nodes.pop();
   }
   
   return *this;
}

#endif // BST_H
