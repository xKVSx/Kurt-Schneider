#include <iostream>
#include <cstring>
#include <cassert>
#include <iomanip>
#include "Airport.h"

using namespace std;

Airport::Airport(const char *iden, const char *nam, const char *num, int len)
		:runwy(num, len)
{
	id = NULL;
	name = NULL;

	setName(nam);
	setID(iden);
}

Airport::Airport(const Airport &a) 
		:runwy(a.runwy)
{
	id = new char[strlen(a.id) + 1];
	name = new char[strlen(a.name) + 1];

	strcpy(id, a.id);
	strcpy(name, a.name);
}

void Airport::setName(const char *nam)
{
	const int MAX_NAME = 25;

	if(strlen(nam) > MAX_NAME)
	{
		cout << "Name is too long.  Name was changed to default value." << endl;
		
		if(name != NULL)
			delete[] name;

		name = new char[MAX_NAME];

		assert(name != NULL);
		strcpy(name, " ");
	}
	else
	{
		if(name != NULL)
			delete[] name;

		name = new char[strlen(nam) + 1];
	
		assert(name != NULL);
		strcpy(name, nam);
	}
}

void Airport::setID(const char *iden)
{	
	const int MAX_ID = 3;

	if(strlen(iden) > MAX_ID)
	{
		cout << "ID is too long.  ID was changed to default value." << endl;
		
		if(id != NULL)
			delete[] id;

		id = new char[MAX_ID];

		assert(id != NULL);
		strcpy(id, " ");
	}
	else
	{
		if(id != NULL)
			delete[] id;

		id = new char[strlen(iden) + 1];

		assert(id != NULL);
		strcpy(id, iden);
	}
}

void Airport::setRunway(const char *num, const int len)
{
	runwy.setLength(len);
	runwy.setNum(num);
}

void Airport::setLength(const int len)
{
	runwy.setLength(len);
}

void Airport::setNum(const char *num)
{
	runwy.setNum(num);
}

void Airport::displayAirport()
{
	cout << id << setw(27) << name << setw(10);
	runwy.displayRunway();
}

Airport::~Airport()
{
	delete[] id;
	delete[] name;
}

const Airport& Airport::operator=(const Airport &A)
{
	if(this != &A)
	{
		delete[] id;
		id = new char[strlen(A.id) + 1];
		assert(id != NULL);
		strcpy(id, A.id);

		delete[] name;
		name = new char[strlen(A.name) + 1];
		assert(name != NULL);
		strcpy(name, A.name);

		runwy = A.runwy;
	}

	return *this;
}

ostream& operator<<(ostream& out, Airport *A)
{
	A->displayAirport();

	return out;
}

ostream& operator<<(ostream& out, Airport A)
{
	A.displayAirport();

	return out;
}




