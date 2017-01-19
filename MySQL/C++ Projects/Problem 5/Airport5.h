#pragma once
#include<string>

using namespace std;

class Airport
{
	friend ostream &operator<<(ostream &out, const Airport &A);

	public:
		Airport(string iden = "", string nam = "", int runnum = 0);
				//pre-condition: none
				//post-condition: sets airport identifier, name, number and length
		Airport(const Airport &a);
				//pre-condition: Airport
				//post-condition: Copies airport
		const Airport& operator=(const Airport& A);
				//pre-condition: Airport
				//post-condition: Assign info of one airport object into another airport object
		bool operator<(const Airport& A) const;
				//pre-condition: Airport
				//post-condition: if id is less than A.id, return true.  If not, return false.
		bool operator>(const Airport& A) const;
				//pre-condition: Airport
				//post-condition: if id is less than A.id, return false.  If not, return true.
		bool operator>=(const Airport& A) const;
				//pre-condition: Airport
				//post-condition: if id is less than or equal to A.id, return false.  If not, return true.
		bool operator<=(const Airport& A) const;
				//pre-condition: Airport
				//post-condition: if id is less than or equal to A.id, return true.  If not, return false.
		bool operator==(const Airport& A) const;
				//pre-condition: list of airports
				//post-condition: if airport id's are equal, return true.  If not, return false.
		void setID(string iden);
				//pre-condition: Identifier
				//post-condition: Checks id against its max and sets id
		void setName(string nam);
				//pre-condition: name
				//post-condition: checks name against max length and sets name
		void setRunway(const int runnum);
				//pre-condition: runway number
				//post-condition:  if number is between 1 and 36, set runway number, else set to default.
		void displayAirport(ostream& out) const;
				//pre-condition: airport and ostream object
				//post-condition: Display airport
		const string getID() const;
				//pre-condition:  Airport
				//post-condition: Return airport id
		const string getName() const;
				//pre-condition: none
				//post-condition:  return airport name
		const int getRunway() const;
				//pre-condition: none
				//post-condition:  return airport runway number
	private:
		char id[4];
		char name[26];
		int runway;
};