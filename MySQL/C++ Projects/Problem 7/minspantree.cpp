#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <set>
#include <iterator>
#include <algorithm>

using namespace std;

void parse(pair<string, string> &wordPair, bool &first, char tempChar, string &tempWord, map<pair<string, string>, int> &freq, map<string, multimap<int, string>> &graph);
typedef map<pair<string, string>, int> wordCount;
typedef set<string> usedNodes;
typedef multimap<int, string> sgraph;
typedef map<string, sgraph> graph;
typedef multimap<int, string> minspantree;

int main()
{
	bool first = true;
	wordCount freq;
	wordCount::iterator iter1;
	usedNodes un;
	usedNodes::iterator iter2;
	graph g;
	graph::iterator iter3;
	sgraph sg;
	sgraph::iterator iter4;
	minspantree mst;
	minspantree::iterator iter5;
	
	char tempChar;
	int minSum = 0;
	string tempWord;
	ifstream myfile;
	pair<string, string> wordPair;
	
	myfile.open("mobysmall.txt");

	if(myfile.is_open())
	{
		myfile.get(tempChar);
		parse(wordPair, first, tempChar, tempWord, freq, g);

		while(!myfile.eof())
		{
			myfile.get(tempChar);
			parse(wordPair, first, tempChar, tempWord, freq, g);
		}
	}
	
	for(iter1 = freq.begin(); iter1!= freq.end(); ++iter1)
	{
		g[iter1->first.first].insert(make_pair(iter1->second, iter1->first.second)); 
		g[iter1->first.second].insert(make_pair(iter1->second, iter1->first.first));
	}

	myfile.close();

	iter3 = g.begin();
	un.insert(iter3->first);

	while(un.size() != g.size())
	{
		for(iter4 = iter3->second.begin(); iter4 != iter3->second.end(); ++iter4)
			mst.insert(make_pair(iter4->first, iter4->second));	

			do{
			iter5 = mst.begin();
			iter2 = un.find(iter5->second);
			if(iter2 == un.end())
			{
				un.insert(iter5->second);
				minSum = minSum + iter5->first;
				iter3 = g.find(iter5->second);
				mst.erase(iter5);
			}
			else
				mst.erase(iter5);
			}while(iter2 != un.end());
	}

	cout << minSum << endl;

	return 0;
}

void parse(pair<string, string> &wordPair, bool &first, char tempChar, string &tempWord, map<pair<string, string>, int> &freq, map<string, sgraph> &graph)
{
	int i = 0;
	bool swap = false;
	wordCount::iterator temp;
	string temps;
	sgraph sg;

	if((tempChar >= 65) && (tempChar <= 90))
	{
		tempChar = tempChar + 32;
		tempWord = tempWord + tempChar;
	}
	else if((tempChar >= 97) && (tempChar <= 122))
			tempWord = tempWord + tempChar;
	else
	{
		if(first == true && tempWord != "")
		{
			wordPair.first = tempWord;
			graph.insert(make_pair(tempWord, sg));
			first = false;
			tempWord = "";
		}
		else if(tempWord != "")
		{
			wordPair.second = tempWord;
			graph.insert(make_pair(tempWord, sg));
			for(int i = 0; i < 1; i++)
			{
				temp = freq.find(wordPair);
				if(temp != freq.end())
					break;
				else
				{
					swap = true;
					temps = wordPair.first;
					wordPair.first = wordPair.second;
					wordPair.second = temps;
				}
			}
			freq[wordPair]++;
			if(swap == false)
				wordPair.first = wordPair.second;
			else
				wordPair.first = wordPair.first;
			tempWord = "";
		}
	}
}