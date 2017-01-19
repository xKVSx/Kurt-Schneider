#pragma once
#include "Airport2.h"

class NonToweredAirport: public Airport
{
	friend ostream &operator<<(ostream &out, const NonToweredAirport &nta);

	public:
		NonToweredAirport(const char *iden = "", const char *nam = "", const char *num = "", int len = 0, const double freq = 0.0);
		const NonToweredAirport& operator=(const NonToweredAirport &nta);
		void setFrequency(const double freq);
		const double getFrequency() const;
		virtual void displayAirport(ostream &out) const;
	private:
		double frequency;
};

