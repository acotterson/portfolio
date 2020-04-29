#pragma warning(disable : 4996)	//visual studio doesn't like the way strcpy was used, so I had to disable the related errors
/***********************************************************************
* Program:
*    Sorting
* Author:
*    Alec Otterson
* Summary:
*	Run the geneology program to output useful files.
************************************************************************/

#include <iostream>        // for CIN and COUT
#include <cstring>         // for strcmp
#include <iomanip>         // for SETW
#include <string>
#include <fstream>
#include "list.h"
#include "person.h"
#include "bst.h"
#include "merge.h"
using namespace std;

//forward declarations
int readFile(char *filename, List<Person> &family, BST<Person> &fTree);



/**********************************************************************
* MAIN
* Gets the sort type and filename from the command line. If the sort type
* or filename are not entered on the command line, the user will be
* prompted for the sort type and/or filename.
* Call the appropriate sort to sort the data contained in the vector or
* linked list and display the sorted data to the console.
***********************************************************************/
int main(int argc, const char* argv[])
{
	char fileName[50];
	if (argc == 1)
	{
		cout << "Enter name of file to sort: ";
		cin >> fileName;
	}
	else if (argc == 2)
	{
		strcpy(fileName, argv[1]);
	}


	//make vector for the data, and read file into it
	List<Person> family;
	BST<Person> fTree;
	if (readFile(fileName, family, fTree) != 1)
	{
		cout << "ERROR: could not open file" << endl;
	}

	family.level();
	mergeSort(family);


	ofstream outFile("sorted.dat");
	for (ListIterator<Person> it = family.begin(); it != family.end(); it++)
	{
		outFile << *it;
	}

	return 0;
}

/**********************************************************************
* ReadFile
* read the file into a list data type
***********************************************************************/
int readFile(char *filename, List<Person> &family, BST<Person> &fTree)
{
	//read file and push each element onto the list
	ifstream file;
	file.open(filename);
	string str;
	getline(file, str);
	while (!file.eof())
	{
		if (str.size() != 0 && str.substr(0, 4) != "0 @F")
			getline(file, str);
		if (file.eof())
			break;
		if (str.size() != 0 && str.substr(0, 3) == "0 @")
		{
			if (str[3] == 'I')
			{
				Person p;
				string num;
				for (int i = 4; str[i] != '@'; i++)
					num += str[i];
				p.id = stoi(num);
				while (str[0] != '2')
				{
					getline(file, str);
				}
				if (str.substr(0, 3) == "2 G")
				{
					p.fName = str.substr(7, str.size());
					do
					{
						getline(file, str);
					} while (str.substr(0, 3) != "1 B" && str.substr(0, 3) != "2 D" && str.substr(0, 3) != "2 S");
				}
				if (str.substr(0, 3) == "1 B" || str.substr(0, 3) == "2 D")
					getline(file, str);
				if (str.substr(0, 3) == "2 S")
				{
					p.lName = str.substr(7, str.size());
					do
					{
						getline(file, str);
					} while (str.substr(0, 3) != "1 B" && str.substr(0, 3) != "2 D");
					getline(file, str);
				}
				if (str.substr(0, 3) == "2 D")
				{
					p.bDate = str.substr(7, str.size());
				}
				family.push_back(p);
			}
			else if (str[3] == 'F')
			{
				int fat = 0;
				int mot = 0;
				int chi = 0;

				do
				{
					getline(file, str);
				} while (str[2] != 'H' && str[2] != 'W' && str[2] != 'C' && str[2] != '@');
				if (str[2] == 'H')
				{
					string tmp;
					for (int i = 9; str[i] != '@'; i++)
						tmp += str[i];
					fat = stoi(tmp);
					getline(file, str);
				}
				if (str[2] == 'W')
				{
					string tmp;
					for (int i = 9; str[i] != '@'; i++)
						tmp += str[i];
					mot = stoi(tmp);
					getline(file, str);
				}
				if (str[2] == 'C')
				{
					string tmp;
					for (int i = 9; str[i] != '@'; i++)
						tmp += str[i];
					chi = stoi(tmp);
					getline(file, str);
				}
				if (chi != 0)
				{
					family.addParents(chi, fat, mot);
				}
			}
		}
	}
	file.close();

	return 1;
}