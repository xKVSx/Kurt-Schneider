#include <iostream>
#include <cstring>
#include <cassert>
#include <iomanip>
#include "Airport2.h"

using namespace std;

Airport::Airport(const char *iden, const char *nam, const char *num, int len)
		:runwy(num, len)
{
	//pre-condition: none
	//post-condition: sets airport identifier, name, number and length

	id = NULL;
	name = NULL;

	setName(nam);
	setID(iden);
}

Airport::Airport(const Airport &a) 
		:runwy(a.runwy)
{
	//pre-condition: Airport
	//post-condition: Copies airport

	id = new char[strlen(a.id) + 1];
	assert(id != NULL);
	name = new char[strlen(a.name) + 1];
	assert(name != NULL);

	strcpy(id, a.id);
	strcpy(name, a.name);
}

void Airport::setName(const char *nam)
{
	//pre-condition: name
	//post-condition: checks name against max length and sets name

	const int MAX_NAME = 25;

	if(strlen(nam) > MAX_NAME)
	{
		cout << "Name is too long.  Name was changed to default value." << endl;
		
		if(name != NULL)
			delete[] name;

		name = new char[MAX_NAME];

		assert(name != NULL);
		strcpy(name, "");
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
	//pre-condition: Identifier
	//post-condition: Checks id against its max and sets id

	const int MAX_ID = 3;

	if(strlen(iden) > MAX_ID)
	{
		cout << "ID is too long.  ID was changed to default value." << endl;
		
		if(id != NULL)
			delete[] id;

		id = new char[MAX_ID];

		assert(id != NULL);
		strcpy(id, "");
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
	//pre-condition: number and length
	//post-condition: sets runway number and length

	runwy.setLength(len);
	runwy.setNum(num);
}

void Airport::setLength(const int len)
{
	//pre-condition: length
	//post-condition: sets runway length

	runwy.setLength(len);
}

void Airport::setNum(const char *num)
{
	//pre-condition: number
	//post-condition: sets runway number

	runwy.setNum(num);
}

void Airport::displayAirport(ostream& out) const
{
	//pre-condition: Airport
	//post-condition: Display airport

	out << left << setw(5) << id << setw(27) << left << name << right << setw(5);
	out << runwy;
}

Airport::~Airport()
{
	//pre-condition: Airport
	//post-condition: Deallocate memory for id and name

	delete[] id;
	delete[] name;
}

const Airport& Airport::operator=(const Airport &A)
{
	//pre-condition: Airport
	//post-condition: Assign info of one airport object into another airport object

	if(this != &A)
	{
		delete[] id;
		setID(A.id);

		delete[] name;
		setName(A.name);

		runwy = A.runwy;
	}

	return *this;
}

ostream& operator<<(ostream &out, const Airport &A)
{
	//pre-condition: Airport
	//post-condition: Display airport

	A.displayAirport(out);

	return out;
}



