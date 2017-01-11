#pragma once
#include "Airport2.h"

class ToweredAirport: public Airport
{
	friend ostream &operator<<(ostream &out, const ToweredAirport &ta);

	public:
		ToweredAirport(const char *iden = "", const char *nam = "", const char *num = "", int len = 0, const char *pia = "");
		ToweredAirport(const ToweredAirport &ta);
		const ToweredAirport& operator=(const ToweredAirport &ta);
		void setApproach(const char *pia); //pia means primary instrument approach
		const char *getApproach() const;
		virtual void displayAirport(ostream &out) const;
		virtual ~ToweredAirport();
	private:
		char *approach;
};




