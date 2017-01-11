#pragma once

using namespace std;

class Airport
{
	friend ostream &operator<<(ostream &out, const Airport &A);

	public:
		Airport(const char *iden = "", const char *nam = "");
		Airport(const Airport &a);
		const Airport& operator=(const Airport& A);
		bool operator<(const Airport& A) const;
		bool operator>(const Airport& A) const;
		bool operator>=(const Airport& A) const;
		bool operator<=(const Airport& A) const;
		bool operator==(const Airport& A) const;
		void setID(const char *iden);
		void setName(const char *nam);
		void displayAirport(ostream& out) const;
		const char *getID() const;
		const char *getName() const;
		~Airport();
	private:
		char *id;
		char *name;
};


