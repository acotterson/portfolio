###############################################################
# Program:
#     Geneology
# Author:
#     Alec Otterson
# Summary:
#     A  program to turn a gedcom into relevant files.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: genealogy.o person.o
	g++ -o a.out genealogy.o person.o -g
	tar -cf genealogy.tar *.h *.cpp makefile

##############################################################
# The individual components
#      genealogy.o     : the driver program
#      spellCheck.o   : the spell-check program and driver
##############################################################
genealogy.o: genealogy.cpp list.h merge.h person.h
	g++ -std=c++11 -c genealogy.cpp -g

person.o: person.h person.cpp
	g++ -std=c++11 -c person.cpp -g

