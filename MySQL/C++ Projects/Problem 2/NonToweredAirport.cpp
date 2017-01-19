#include <iostream>
#include <cstring>
#include <cassert>
#include <iomanip>
#include "NonToweredAirport.h"

using namespace std;

NonToweredAirport::NonToweredAirport(const char *iden, const char *nam, const char *num, int len, const double freq)
			      :Airport(iden, nam, num, len)
{
	//pre-condition: none
	//post-condition: sets airport identifier, name, number, runway length and frequency

	setFrequency(freq);
}

void NonToweredAirport::setFrequency(const double freq)
{
	//pre-condition: prompt for frequency
	//post-condition: makes sure frequency is non-negative and sets frequency.  If non-negative, sets frequency to 0

	if(freq >= 0)
		frequency = freq;
	else
		frequency = 0;
}

const double NonToweredAirport::getFrequency() const
{
	//pre-condition: none
	//post-condition: returns frequency

	return frequency;
}

void NonToweredAirport::displayAirport(ostream &out) const
{
	//pre-condition: Airport list
	//post-condition: Displays the airport list

	Airport::displayAirport(out);
	out << setw(10) << frequency << endl;
}

const NonToweredAirport& NonToweredAirport::operator =(const NonToweredAirport &nta)
{
	//pre-condition: Airport list
	//post-condition: Assigns airport list a copy

	if(this != &nta)
	{
		Airport::operator =(nta);
		frequency = nta.frequency;
	}

	return *this;
}

ostream &operator<<(ostream &out, const NonToweredAirport &nta)
{
	//pre-condition: Airport list
	//post-condition: displays airport list

	nta.displayAirport(out);

	return out;
}
