#pragma once

using namespace std;

struct Index5
{
	char *id;
	int RRN;
	bool operator<(const Index5& I) const;
};

