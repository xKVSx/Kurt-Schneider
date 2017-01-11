#include <iostream>
#include <cstring>
#include <cassert>
#include <iomanip>
#include "Runway2.h"

using namespace std;

Runway::Runway(const char *num, int len)
{
	//pre-condition: none
	//post-condition: sets runway number and length

	number = NULL;

	setNum(num);
	setLength(len);
}

Runway::Runway(const Runway &r)
{
	//pre-condition: Runway
	//post-condition: Copies runway length and number.  If number already exist, delete and reset.

	length = r.length;
	number = new char[strlen(r.number) + 1];
	assert(number != NULL);

	strcpy(number, r.number);
}

void Runway::setNum(const char *num)
{
	//pre-condition: none
	//post-condition: checks number for proper length and sets number

	const int MAX_NUM = 3;

	if(strlen(num) > MAX_NUM)
	{
		cout << "Runway number is too long.  Runway number was changed to default value." << endl;
		
		if(number != NULL)
			delete[] number;

		number = new char[MAX_NUM];
		assert(number != NULL);
		strcpy(number, "");
	}
	else
	{
		if(number != NULL)
			delete[] number;

		number = new char[strlen(num) + 1];

		assert(number != NULL);
		strcpy(number, num);
	}
}

void Runway::setLength(int len)
{
	//pre-condition: none
	//post-condition: checks for non-negative values.  If non-negative, set length

	if(len < 0)
	{
		cout << "Invalid length.  Length was changed to default value." << endl;
		length = 0;
	}
	else
		length = len;
}

void Runway::displayRunway(ostream &out) const
{
	//pre-condition: none
	//post-condition: display runway

	out << number << setw(10) << length;
}

const char *Runway::getNum() const
{
	//pre-condition: none
	//post-condition: return number

	return number;
}

const int Runway::getLength() const
{
	//pre-condition: none
	//post-condition: return length

	return length;
}

Runway::~Runway()
{
	//pre-condition: none
	//post-condition: deallocate memory for number

	delete[] number;
}

const Runway& Runway::operator=(const Runway &R)
{
	//pre-condition: Runway
	//post-condition: Assigns runway info of one object nto another runway object

	if(this != &R)
	{
		delete[] number;
		setNum(R.number);

		length = R.length;
	}

	return *this;
}

ostream& operator<<(ostream &out, const Runway &R)
{
	//pre-condition: Runway
	//post-condition: Displays runway

	R.displayRunway(out);

	return out;
}
