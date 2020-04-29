/***********************************************************************
* Module:
*    Person
* Author:
*    Helfrich
* Summary:
*    This program will implement a person
************************************************************************/
#pragma once

#include <iostream>  // for ISTREAM and OSTREAM
#include <string>

using namespace std;
/**********************************************
* PAIR
* This class couples together a pair of values, which may be of
* different types (T1 and T2). The individual values can be
* accessed through its public members first and second.
*
* Additionally, when compairing two pairs, only T1 is compared. This
* is a key in a name-value pair.
***********************************************/



class Person
{
public:
	// constructors
	Person() : fName(), lName(), bDate(), id() {}
	Person(const string & first, const string & last, const string & date, int ident) : fName(first), lName(last), bDate(date), id(ident) {}
	Person(const Person & rhs) : fName(rhs.fName), lName(rhs.lName), bDate(rhs.bDate), id(rhs.id) {}

	// copy the values
	Person & operator = (const Person & rhs)
	{
		fName = rhs.fName;
		lName = rhs.lName;
		bDate = rhs.bDate;
		id = rhs.id;
		return *this;
	}

	// constant fetchers
	const string & getFName()  const { return fName; }
	const string & getLName() const { return lName; }
	const string & getBDate() const { return bDate; }
	const int & getID() const { return id; }


	// compare people.
	bool operator >  (const Person & rhs) const;
	bool operator >=  (const Person & rhs) const;
	bool operator == (const int & rhs) const;

	// these are public.  We cannot validate!
	string fName;
	string lName;
	string bDate;
	int id;
};

/*****************************************************
* Person INSERTION
* Display a person for debug purposes
****************************************************/
inline std::ostream & operator << (std::ostream & out, const Person & rhs)
{
	if (rhs.fName.size() != 0)
		out << rhs.fName;
	if (rhs.fName.size() != 0 && rhs.lName.size() != 0 )
		out << ' ';
	if (rhs.lName.size() != 0)
		out << rhs.lName;
	if (rhs.bDate.size() != 0)
		out << ", b. " << rhs.bDate;
	out << endl;
	return out;
}

/*****************************************************
* Person EXTRACTION
* input a person
****************************************************/
inline std::istream & operator >> (std::istream & in, Person & rhs)
{
	in >> rhs.fName >> rhs.lName >> rhs.bDate;
	return in;
}

