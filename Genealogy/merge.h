/***********************************************************************
* Program:
*    Sorting
*
* Author:
*   Alec Otterson
* Summary:
*	Implementation of the merge sort algorithm.
************************************************************************/
#include "list.h"
#include "person.h"

using namespace std;

//forward declarations
template<class T>
void split(List <T> & oList, List <T> &F1List, List<T> &F2List);

template<class T>
void merge(List <T> & oList, List <T> &F1List, List<T> &F2List);

/*************************************************************************
* This function sorts a linked list using a Natural Merge Sort.
* Input:  data -  linked list of data to be sorted.
* Output: data -  sorted linked list
**************************************************************************/
template<class T>
void mergeSort(List<T> &data)
{
	//create two new lists for when we split
	List<T> F1List;
	List<T> F2List;

	//split the original list
	split(data, F1List, F2List);
	//merge and split until everything is in order (no sublists go to the second list on a split)
	while (!F2List.empty())
	{
		merge(data, F1List, F2List);
		split(data, F1List, F2List);
	}
	//we ended on a split, so the data is in F1List
	data = F1List;
}

/*************************************************************************
* Split
* split the main list into 2 sublists
**************************************************************************/
template<class T>
void split(List<T>& oList, List<T>& F1List, List<T>& F2List)
{
	//create an iterator for the main list
	ListIterator<T> it = oList.begin();

	//set a variable equal to the element (for comparison)
	T el = *it;

	//run until the end of the main list
	while (it != oList.end())
	{
		//push elements from oList onto F1List until oList ends or the current item is less than the previous one
		do
		{
			el = *it;
			F1List.push_back(el);
			it++;
		} while (it != oList.end() && *it > el);

		//if we didn't reach the end of oList
		if (it != oList.end())
		{
			//push items from oList to F2List until oList ends or the current item is less than the previous one
			do
			{
				el = *it;
				F2List.push_back(el);
				it++;
			} while (it != oList.end() && *it > el);
		}
	}
	//clear the oList
	oList.clear();
}

/*************************************************************************
* Merge
* merge the 2 sublists into one main list
**************************************************************************/
template<class T>
void merge(List<T>& oList, List<T>& F1List, List<T>& F2List)
{
	//create an iterator to go through each sublist
	ListIterator<T> it1 = F1List.begin();
	ListIterator<T> it2 = F2List.begin();

	//variables for comparison purposes
	T el1;
	T el2;

	//run until the end of both sublists is reached
	while (it1 != F1List.end() && it2 != F2List.end())
	{
		//push the greater of the current elements of each list onto the main list until the end of a sublist, or the end of one of the lists is reached
		do
		{
			el1 = *it1;
			el2 = *it2;
			if (el2 > el1)
			{
				oList.push_back(el1);
				it1++;
			}
			else
			{
				oList.push_back(el2);
				it2++;
			}
		} while ((it1 != F1List.end() && it2 != F2List.end()) && (*it1 >= el1 && *it2 >= el2));

		//if not at the end of F1List or a sublist within it, push the remaining items in the sublist onto oList
		while (it1 != F1List.end() && *it1 >= el1)
		{
			el1 = *it1;
			oList.push_back(el1);
			it1++;
		}
		//same as above, but with F2List
		while (it2 != F2List.end() && *it2 >= el2)
		{
			el2 = *it2;
			oList.push_back(el2);
			it2++;
		}
	}
	//we reached the end of one of the lists, so we need to copy whatever is left in the remaining list

	//if we're not at the end of F1List, copy the remaining elements from it to oList
	while (it1 != F1List.end())
	{
		el1 = *it1;
		oList.push_back(el1);
		it1++;
	}
	//do the same thing, but for F2List
	while (it2 != F2List.end())
	{
		el2 = *it2;
		oList.push_back(el2);
		it2++;
	}
	
	//clear both the sublists
	F1List.clear();
	F2List.clear();
}

