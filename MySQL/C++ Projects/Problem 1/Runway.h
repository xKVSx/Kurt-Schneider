#pragma once

using namespace std;

class Runway
{
	friend ostream& operator<<(ostream& out, Runway *R);
	friend ostream& operator<<(ostream& out, Runway R);

	public:
		Runway(const char *num = " ", int length = 0);
		Runway(const Runway &r);
		const Runway& operator=(const Runway &R);
		void setNum(const char *num);
		void setLength(int length);
		void displayRunway();
		char * getNum();
		int getLength();
		~Runway();
	private:
		char *number;
		int length;
};

