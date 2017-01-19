#pragma once

using namespace std;

class Runway
{
	friend ostream &operator<<(ostream &out, const Runway &R);

	public:
		Runway(const char *num = "", int length = 0);
		Runway(const Runway &r);
		const Runway& operator=(const Runway &R);
		void setNum(const char *num);
		void setLength(int length);
		void displayRunway(ostream &out) const;
		const char * getNum() const;
		const int getLength() const;
		~Runway();
	private:
		char *number;
		int length;
};

