#include <iostream>
#include <cstring>
#include <cassert>
#include <iomanip>
#include "Runway.h"

using namespace std;

Runway::Runway(const char *num, int len)
{
	number = NULL;

	setNum(num);
	setLength(len);
}

Runway::Runway(const Runway &r)
{
	length = r.length;
	number = new char[strlen(r.number) + 1];

	strcpy(number, r.number);
}

void Runway::setNum(const char *num)
{
	const int MAX_NUM = 3;

	if(strlen(num) > MAX_NUM)
	{
		cout << "Runway number is too long.  Runway number was changed to default value." << endl;
		
		if(number != NULL)
			delete[] number;

		number = new char[MAX_NUM];
		assert(number != NULL);
		strcpy(number, " ");
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
	if(len < 0)
	{
		cout << "Invalid length.  Length was changed to default value." << endl;
		length = 0;
	}
	else
		length = len;
}

void Runway::displayRunway()
{
	cout << number << setw(10) << length;
}

char *Runway::getNum()
{
	return number;
}

int Runway::getLength()
{
	return length;
}

Runway::~Runway()
{
	delete[] number;
}

const Runway& Runway::operator=(const Runway &R)
{
	if(this != &R)
	{
		delete number;
		number = new char[strlen(R.number) + 1];

		assert(number != NULL);
		strcpy(number, R.number);

		length = R.length;
	}

	return *this;
}

ostream& operator<<(ostream& out, Runway *R)
{
	R->displayRunway();

	return out;
}

ostream& operator<<(ostream& out, Runway R)
{
	R.displayRunway();

	return out;
}

