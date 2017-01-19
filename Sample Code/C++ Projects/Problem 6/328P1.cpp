#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

void parse(char tempChar, string &tempWord, map<string, int> &freq);
typedef map<string, int, less<string>> wordCount;
typedef multimap<int, string, less<int>> topWords;

int main()
{
	wordCount freq;
	wordCount::iterator iter1;
	topWords top;
	topWords::reverse_iterator iter2;
	char tempChar;
	int counter = 0;
	string tempWord;
	ifstream myfile;

	myfile.open("C:/moby.txt");

	if(myfile.is_open())
	{
		myfile.get(tempChar);
		parse(tempChar, tempWord, freq);

		while(!myfile.eof())
		{
			myfile.get(tempChar);
			parse(tempChar, tempWord, freq);
		}
	}

	myfile.close();

	iter1 = freq.find("");
	freq.erase(iter1);

	for(iter1 = freq.begin(); iter1 != freq.end(); ++iter1)
		top.insert(topWords::value_type(iter1->second, iter1->first));

	for(iter2 = top.rbegin(); counter < 40; ++counter)
	{
		cout << iter2->second << '\t' << iter2->first << '\n';
		iter2++;
	}
	
	cout << endl;

	return 0;
}

void parse(char tempChar, string &tempWord, map<string, int> &freq)
{
	int i = 0;

	if((tempChar >= 65) && (tempChar <= 90))
	{
		tempChar = tempChar + 32;
		tempWord = tempWord + tempChar;
	}
	else if((tempChar >= 97) && (tempChar <= 122))
			tempWord = tempWord + tempChar;
	else
	{
		freq[tempWord]++;
		tempWord = "";
	}
}

