#include <iostream>
#include <cstring>
#include <cassert>
#include <iomanip>
#include "ToweredAirport.h"

using namespace std;

ToweredAirport::ToweredAirport(const char *iden, const char *nam, const char *num, int len, const char *pia)
			   :Airport(iden, nam, num, len)
{
	//pre-condition: none
	//post-condition: sets airport indentifier, name, number, length and primary instrument approach

	approach = NULL;

	setApproach(pia);
}

ToweredAirport::ToweredAirport(const ToweredAirport &ta) 
		       :Airport(ta)
{
	//pre-condition: Towered airport
	//post-condition: makes a copy of a towered airport

	approach = new char[strlen(ta.approach) + 1];

	strcpy(approach, ta.approach);
}

void ToweredAirport::setApproach(const char *pia)
{
	//pre-condition: primary instrument approach
	//post-condition: checks pia for proper length.  If approach is already defined, delete and re-define.

	const int MAX_PIA = 6;

	if(strlen(pia) > MAX_PIA)
	{
		cout << "Primary instrument approach is too long.  Changed to default value." << endl;
		
		if(approach != NULL)
			delete[] approach;

		approach = new char[MAX_PIA];

		assert(approach != NULL);
		strcpy(approach, " ");
	}
	else
	{
		if(approach != NULL)
			delete[] approach;

		approach = new char[strlen(pia) + 1];

		assert(approach != NULL);
		strcpy(approach, pia);
	}
}

const char *ToweredAirport::getApproach() const
{
	//pre-condition: none
	//post-condition: return primary instrument approach

	return approach;
}

void ToweredAirport::displayAirport(ostream &out) const
{
	//pre-condition: none
	//post-condition: display airport

	Airport::displayAirport(out);
	out << setw(10) << approach << endl;
}

const ToweredAirport& ToweredAirport::operator =(const ToweredAirport &ta)
{
	//pre-condition: Towered airport
	//post-condition: checks for self reference and assigns airport info into another airport

	if(this != &ta)
	{
		Airport::operator =(ta);
		delete[] approach;
		approach = new char[strlen(ta.approach) + 1];
		assert(approach != NULL);
		strcpy(approach, ta.approach);
	}

	return *this;
}

ToweredAirport::~ToweredAirport()
{
	//pre-condition: none
	//post-condition: deallocates primary instrument approach

	delete[] approach;
}

ostream& operator<<(ostream &out, const ToweredAirport &ta)
{
	//pre-condition: Towered airport
	//post-condition: Display towered airport

	ta.displayAirport(out);

	return out;
}