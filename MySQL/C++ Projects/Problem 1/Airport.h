#pragma once
#include "Runway.h"

using namespace std;

class Airport
{
	friend ostream& operator<<(ostream& out, Airport *A);
	friend ostream& operator<<(ostream& out, Airport A);

	public:
		Airport(const char *iden = " ", const char *nam = " ", const char *num = " ", int len = 0);
		Airport(const Airport &a);
		const Airport& operator=(const Airport& A);
		void setID(const char *iden);
		void setName(const char *nam);
		void setRunway(const char *num, const int len);
		void setLength(const int len);
		void setNum(const char *num);
		void displayAirport();
		char *getID();
		char *getName();
		Runway getRunway();
		~Airport();
	private:
		char *id;
		char *name;
		Runway runwy;
};


