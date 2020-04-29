/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). 
 * Author
 *    Alec Otterson
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "bnode.h"

 /***********************************************
  * INSERTION SORT
  * Sort the items in the array
  **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
	//create a new node with the data from the first array element
	Node <T>* hNode = new Node <T>(array[0]);

	//as long as the array still has data, do this
	for (int i = 1; i < num; i++)
	{
		Node <T>* newNode = hNode;		//make newNode pointer point to hNode
		if (hNode->data > array[i])		//if the data in the first node is larger than the data in the current array element
			insert(array[i], hNode, true);	//insert the element as the head node
		else						//do this for all non-head elements
		{
			while (newNode->data < array[i])	//while the data in the newNode location is less thatn the current array element
			{
				if (newNode->pNext == NULL)		//if we are on the last node
					insert(array[i], newNode);	//insert the element after the last node
				else if (newNode->pNext->data > array[i])	//if the data in the next node is greater than the current element
					insert(array[i], newNode);				//insert the element after the current node (a little redundant I suppose, but clear)
				else				//if the data at both this and the next node are smaller than the current element
				{
						newNode = newNode->pNext;	//move the newNode pointer to point to the next node
				}
			}
		}
	}

	for (int i = 0; i < num; i++)	//copy dat from the series of nodes back into the array in order
	{
		array[i] = hNode->data;
		if (hNode->pNext != NULL)
			hNode = hNode->pNext;
	}
}

#endif // INSERTION_SORT_H

