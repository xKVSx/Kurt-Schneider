#pragma once
#include "Runway2.h"

using namespace std;

class Airport
{
	friend ostream &operator<<(ostream &out, const Airport &A);

	public:
		Airport(const char *iden = "", const char *nam = "", const char *num = "", int len = 0);
		Airport(const Airport &a);
		virtual const Airport& operator=(const Airport& A);
		void setID(const char *iden);
		void setName(const char *nam);
		void setRunway(const char *num, const int len);
		void setLength(const int len);
		void setNum(const char *num);
		virtual void displayAirport(ostream& out) const = 0;
		const char *getID() const;
		const char *getName() const;
		Runway getRunway();
		virtual ~Airport();
	private:
		char *id;
		char *name;
		Runway runwy;
};


