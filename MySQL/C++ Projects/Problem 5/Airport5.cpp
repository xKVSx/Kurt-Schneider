#include <iostream>
#include <cstring>
#include <cassert>
#include <iomanip>
#include <string>
#include "Airport5.h"

using namespace std;

Airport::Airport(string iden, string nam, int runnum)
{
	//pre-condition: none
	//post-condition: sets airport identifier, name, number and length

	setName(nam);
	setID(iden);
	setRunway(runnum);
}

Airport::Airport(const Airport &a) 
{
	//pre-condition: Airport
	//post-condition: Copies airport

	strcpy(id, a.id);
	strcpy(name, a.name);
	runway = a.runway;
}

void Airport::setName(string nam)
{
	//pre-condition: name
	//post-condition: checks name against max length and sets name

	const char *airportname = nam.data();
	int length = nam.size();
	length = (length < 26 ? length : 25);
	strncpy(name, airportname, length);
	name[length] = '\0';
}

void Airport::setID(string iden)
{	
	//pre-condition: Identifier
	//post-condition: Checks id against its max and sets id

	const char *airportid = iden.data();
	int length = iden.size();
	length = (length < 4 ? length : 3);
	strncpy(id, airportid, length);
	id[length] = '\0';
}

void Airport::setRunway(const int runnum)
{
	//pre-condition: runway number
	//post-condition:  if number is between 1 and 36, set runway number, else set to default.

	if(runnum >= 1 && runnum <= 36)
		runway = runnum;
	else
		runway = 0;
}

const string Airport::getID() const
{
	//pre-condition:  Airport
	//post-condition: Return airport id

	return id;
}

const string Airport::getName() const
{
	//pre-condition: none
	//post-condition:  return airport name

	return name;
}

const int Airport::getRunway() const
{
	//pre-condition: none
	//post-condition:  return airport runway number

	return runway;
}

void Airport::displayAirport(ostream& out) const
{
	//pre-condition: airport and ostream object
	//post-condition: Display airport

	out << setw(5) << left << id << setw(27) << left << name << setw(5) << runway;
}

const Airport& Airport::operator=(const Airport &A)
{
	//pre-condition: Airport
	//post-condition: Assign info of one airport object into another airport object

	if(this != &A)
	{
		strcpy(id, A.id);
		strcpy(name, A.name);
		runway = A.runway;
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

bool Airport::operator>(const Airport& A) const
{
	//pre-condition: Airport
	//post-condition: if id is less than A.id, return false.  If not, return true.

	if((strcmp(id, A.id)) > 0)
		return true;
	else
		return false;
}

bool Airport::operator <=(const Airport& A) const
{
	//pre-condition: Airport
	//post-condition: if id is less than or equal to A.id, return true.  If not, return false.

	if((strcmp(id, A.id)) <= 0)
		return true;
	else
		return false;
}

bool Airport::operator >=(const Airport& A) const
{
	//pre-condition: Airport
	//post-condition: if id is less than or equal to A.id, return false.  If not, return true.

	if((strcmp(id, A.id)) >= 0)
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