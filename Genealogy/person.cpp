/***********************************************************************
* Program:
*    Genealogy
* Author:
*    Alec Otterson
* Summary:
*	Implement a person class
************************************************************************/
#include "person.h"

bool Person::operator>(const Person & rhs) const
{
	string tmp1;
	string tmp2;
	for (int i = 0; i < this->lName.size(); i++)
	{
		tmp1 += tolower(this->lName[i]);
	}
	for (int i = 0; i < rhs.lName.size(); i++)
	{
		tmp2 += tolower(rhs.lName[i]);
	}
	if (((this->lName.size() > 0 && rhs.lName.size() > 0) && tmp1 > tmp2) || (this->lName.size() > 0 && rhs.lName.size() == 0))
		return true;
	else if ((this->lName.size() == 0 && rhs.lName.size() == 0) || this->lName == rhs.lName)
	{
		tmp1.clear();
		tmp2.clear();
		for (int i = 0; i < this->fName.size(); i++)
		{
			tmp1 += tolower(this->fName[i]);
		}
		for (int i = 0; i < rhs.fName.size(); i++)
		{
			tmp2 += tolower(rhs.fName[i]);
		}
		if (this->fName > rhs.fName)
			return true;
		else if (this->fName == rhs.fName)
		{
			int iYear = 0;
			int rIYear = 0;
			if (this->bDate.size() > 0)
			{
				string year = this->bDate.substr(this->bDate.size() - 4);
				iYear = stoi(year);
			}

			if (rhs.bDate.size() > 0)
			{
				string rYear = rhs.bDate.substr(rhs.bDate.size() - 4);
				rIYear = stoi(rYear);
			}
			if (iYear > rIYear)
				return true;
		}
	}
	return false;
}

bool Person::operator>=(const Person & rhs) const
{
	if ((*this > rhs) || this->id == rhs.id)
		return true;
	return false;
}

bool Person::operator==(const int & rhs) const
{
	if (this->id == rhs)
		return true;
	return false;
}

