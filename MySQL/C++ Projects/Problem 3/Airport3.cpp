#include <iostream>
#include <cstring>
#include <cassert>
#include <iomanip>
#include "Airport3.h"

using namespace std;

Airport::Airport(const char *iden, const char *nam)
{
	//pre-condition: none
	//post-condition: sets airport identifier, name, number and length

	id = NULL;
	name = NULL;

	setName(nam);
	setID(iden);
}

Airport::Airport(const Airport &a) 
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

const char* Airport::getID() const
{
	//pre-condition:  Airport
	//post-condition: Return airport id

	return id;
}

void Airport::displayAirport(ostream& out) const
{
	//pre-condition: Airport
	//post-condition: Display airport

	out << setw(5) << left << id << setw(27) << left << name;
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
		id = new char[strlen(A.id) + 1];
		assert(id != NULL);
		strcpy(id, A.id);

		delete[] name;
		name = new char[strlen(A.name) + 1];
		assert(name != NULL);
		strcpy(name, A.name);
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

bool Airport::operator <(const Airport &A) const
{
	//pre-condition: Airport
	//post-condition: if id is less than A.id, return true.  If not, return false.

	if((strcmp(id, A.id)) < 0)
		return true;
	else
		return false;
}

bool Airport::operator ==(const Airport &A) const
{
	//pre-condition: list of airports
	//post-condition: if airport id's are equal, return true.  If not, return false.

	if((strcmp(id, A.id)) == 0)
		return true;
	else
		return false;
}




