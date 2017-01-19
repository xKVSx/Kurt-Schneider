#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cctype>
#include <set>
#include <map>
#include <iterator>
#include <algorithm>
#include "Airport5.h"

using namespace std;

struct arptIndex
{
	char id[4];
	int RRN;
	void setID(string iden)
	{	
		const char *airportid = iden.data();
		int length = iden.size();
		length = (length < 4 ? length : 3);
		strncpy(id, airportid, length);
		id[length] = '\0';
	};
	bool operator<(const arptIndex& ai) const
	{
		if((strcmp(id, ai.id)) < 0)
			return true;
		else
			return false;
	};
};

int getValidInt();
	//pre-condition: prompt user input
	//post-condition:  if input is valid, return input as integer.  
	//If not valid, re-prompt user for input.
void program_intro();
	//pre-condition: none.
	//post-condition: display the purpose of the program.
void getMenuOption();
	//pre-condition: none.
	//post-condition:  display main menu options.
void Header();
	//pre-condition:  none
	//post-condition: display airport header
void setID(char *id, const int MAX_ID);
	//pre-condition:  prompt user for the airport id
	//post-condition:  if airport id is valid, set id.  
	//if airport id is too large, re-prompt user.
void setName(char *name, const int MAX_NAME);
	//pre-condition:  prompt user for airport name
	//post-condition:  if airport name is valid, set name.  
	//if airport name is too large, re-prompt user.
void setRunway(int &runway);
	//pre-condition: prompts user for runway number
	//post-condition: sets runway number.
bool checkFiles(fstream &indexFile, fstream &masterFile);
	//pre-condition: index file and main file
	//post-condition:  if files do not exist, create them.  
	//If index file already exist, return true
void readIfile(fstream &indexFile, arptIndex &iContainer, set<arptIndex> &Index, int &RRN);
	//pre-condition: index file, airport index, airport index set, RRN
	//post-condition:  read from index file and place information into set
void addToMain(set<arptIndex> &tempf, const Airport &tempa, const arptIndex &tempc, int &rrn, fstream &mfile);
	//pre-condition: Airport index set, airport index, airport, rrn, main file
	//post-condition:  if airport does not already exist, add airport to main file
void setarptIndex(arptIndex &aindex, const Airport &tempa, int &rrn);
	//pre-condition: Airport index, Airport, RRN
	//post-condition:  set airport index id and RRN
void deleteAirport(set<arptIndex> &Index, fstream &mfile);
	//pre-condition: airport index set, main file
	//post-condition:  if airport exist, delete airport from main file by placing * in
	//in the first byte of the record.  Delete airport from set.
void displayAirport(set<arptIndex> &Index, fstream &mfile);
	//pre-condition: airport index set, main file
	//post-condition:  if airport exist, display airport from main file
void displayAirports(set<arptIndex> &Index, fstream &mfile);
	//pre-condition: airport index set, main file
	//post-condition:  display all airports on main file
void changeRunwayNumber(set<arptIndex> &Index, fstream &mfile);
	//pre-condition: airport index set, main file
	//post-condition:  change runway number for an airport and update main file
Airport setAirportInfo();
	//pre-condition: none.
	//post-condition: creates, sets, and returns a towered airport.
void updateIndexFile(const set<arptIndex> &list, fstream &mfile);
	//pre-condition: Airport index set
	//post-condition:  Update index file
typedef set<arptIndex> IndexFile;

int main()
{
	// Declaration and initialization of variables
	int menu_option, RRN = 0;
	arptIndex iContainer;
	Airport airport;
	IndexFile Index;
	fstream ifile; 
	fstream mfile;

	if(checkFiles(ifile, mfile)) //If true, index file already exist
		readIfile(ifile, iContainer, Index, RRN);

	program_intro(); // Display the program's purpose
	cout << endl;  

		do {
		// Display the menu and get the menu option
		getMenuOption();
		menu_option = getValidInt();
		
		switch (menu_option) 
		{
			case 1:	// Enter an airport into the list
				cout << endl;		
				airport = setAirportInfo(); 
				//creates airport
				setarptIndex(iContainer, airport, RRN); 
				//places airport into struct
				addToMain(Index, airport, iContainer, RRN, mfile); 
				//places struct object into set and writes airport to main file
				break;
			case 2:  //delete an airport from the list
				deleteAirport(Index, mfile);
				break;
			case 3:	//locate and display an airport
				displayAirport(Index, mfile);
				break;
			case 4: //change the runway number
				changeRunwayNumber(Index, mfile);
				break;
			case 5:	//display airports in ascending identifier order
				displayAirports(Index, mfile);
				break;
			case 6: //update index file
				updateIndexFile(Index, mfile);
				break;
				default:  //Invalid menu option
					cout << "Invalid menu option.  Please re-enter." << endl;
					break;
		}  //end switch statement
	} while (menu_option != 6);	//end do-while loop

	return 0;
}

void program_intro()
{
	//pre-condition: none.
	//post-condition: display the purpose of the program.

	cout << "The program will add, locate and delete airport records from a file." << endl; 
	cout << "***************************************************************************" << endl;
}

void getMenuOption()
{
	//pre-condition: none.
	//post-condition:  display main menu options.

	cout << "Main Menu" << endl << "======================" << endl;
	cout << "Press 1 to enter an airport into the list." << endl;
	cout << "Press 2 to delete an airport from the list." << endl;
	cout << "Press 3 to locate and display an airport." << endl;
	cout << "Press 4 to change the runway number of an airport." << endl;
	cout << "Press 5 display all airports in ascending identifier order." << endl;
	cout << "Press 6 to exit the program." << endl << "======================" << endl << endl;
	cout << "Enter menu option: ";
}

int getValidInt()
{
	//pre-condition: prompt user input
	//post-condition:  if input is valid, return input as integer.  
	//If not valid, re-prompt user for input.

	const int MAX = 80;
	char buffer[MAX];
	int i;

	cin.getline(buffer, MAX); //prompt user for input

	while((strlen(buffer)) != strspn(buffer, "0123456789"))
	{
		cout << "Invalid option - please re-enter: ";
		cin.getline(buffer, MAX);
	}

	i = atoi(buffer);

	return i;
}

Airport setAirportInfo()
{
	//pre-condition: none.
	//post-condition: creates, sets, and returns a towered airport.

	const int MAX_ID = 4;
	const int MAX_NAME = 26;
	int runway;
	char id[MAX_ID];
	char name[MAX_NAME];

	setID(id, MAX_ID);
	setName(name, MAX_NAME);
	setRunway(runway);
	Airport aprt(id, name, runway);

	return aprt;
}

void setID(char *id, const int MAX_ID)
{
	//pre-condition:  prompt user for the airport id
	//post-condition:  if airport id is valid, set id.  
	//if airport id is too large, re-prompt user.

	const int MAX_BUFFER = 80;
	char buffer[MAX_BUFFER];
	int counter = 0;

	cout << "Enter airport ID: ";
	cin.getline(buffer, MAX_BUFFER);

	while((strlen(buffer)) >= MAX_ID)
	{
		cout << "ID is too long - please re-enter: ";
		cin.getline(buffer, MAX_BUFFER);
	}

	while(counter <= MAX_ID)
	{
		buffer[counter] = (toupper(buffer[counter]));
		counter++;
	}

	strcpy(id, buffer);
}

void setRunway(int &runway)
{
	//pre-condition: prompts user for runway number
	//post-condition: sets runway number.

	const int MAX = 80;
	char buffer[MAX];

	cout << "Enter the runway number: ";
	runway = getValidInt();

	while(runway < 1 || runway > 36)
	{
		cout <<"Invalid runway number - please re-enter:";
		runway = getValidInt();
	}
}

void setName(char *name, const int MAX_NAME)
{
	//pre-condition:  prompt user for airport name
	//post-condition:  if airport name is valid, set name.  
	//if airport name is too large, re-prompt user.

	const int MAX_BUFFER = 80;
	char buffer[MAX_BUFFER];

	cout << "Enter airport name: ";
	cin.getline(buffer, MAX_BUFFER);

	while((strlen(buffer)) >= MAX_NAME)
	{
		cout << "Airport name is too long - please re-enter: ";
		cin.getline(buffer, MAX_BUFFER);
	}

	strcpy(name, buffer);
}

void Header()
{
	//pre-condition:  none
	//post-condition: display airport header

	cout << left << endl;
	cout << setw(5) << "ID" << setw(7) << "Name" << right << setw(33) << "Runway Number" << endl;
	cout <<"_____________________________________________" << endl;
}

void setarptIndex(arptIndex &aindex, const Airport &tempa, int &rrn)
{
	//pre-condition: Airport index, Airport, RRN
	//post-condition:  set airport index id and RRN

	aindex.setID(tempa.getID());
	aindex.RRN = rrn++;
}

void addToMain(set<arptIndex> &tempf, const Airport &tempa, const arptIndex &tempc, int &rrn, fstream &mfile)
{
	//pre-condition: Airport index set, airport index, airport, rrn, main file
	//post-condition:  if airport does not already exist, add airport to main file

	pair<IndexFile::const_iterator, bool> dpl;  //pair to determine if airport was inserted

	dpl = tempf.insert(IndexFile::value_type(tempc)); //insert airport into set

	if(dpl.second == true)  //if insertion was true, write airport to main file
	{	
		mfile.seekp(0);
		mfile.seekp((tempc.RRN) * sizeof(Airport));
		mfile.write(reinterpret_cast<const char *>(&tempa), sizeof(Airport));
		cout << endl << "Airport stored in list." << endl << endl;
	}
	else
	{
		cout << endl << "Airport ID already exist.  Airport was not stored in list." << endl << endl;
		rrn--; //decrement rrn since airport already exist
	}
}

void updateIndexFile(const set<arptIndex> &list, fstream &mfile)
{
	//pre-condition: Airport index set
	//post-condition:  Update index file

	int count = 0;
	fstream ifile; 
	arptIndex tempContainer;

	ifile.open("indexfile.bin", ios::out | ios::binary);

	for(IndexFile::const_iterator iter = list.begin(); iter != list.end(); iter++)
	{
		tempContainer.setID(iter->id);
		tempContainer.RRN = iter->RRN;
		ifile.seekp((count++) * sizeof(arptIndex));
		ifile.write(reinterpret_cast<const char *>(&tempContainer), sizeof(arptIndex));
	}
	ifile.close();
	ifile.clear();
	mfile.close();
	mfile.clear();
}

bool checkFiles(fstream &indexFile, fstream &masterFile)
{
	//pre-condition: index file and main file
	//post-condition:  if files do not exist, create them.  
	//If index file already exist, return true

	masterFile.open("masterfile.bin", ios::in);
	indexFile.open("indexfile.bin", ios::in);

	if(!masterFile)
	{
		masterFile.close();
		masterFile.clear();
		masterFile.open("masterfile.bin", ios::out | ios::binary);
	}

	masterFile.close();
	masterFile.clear();
	masterFile.open("masterfile.bin", ios::in | ios::out | ios::binary);

	if(!indexFile)
	{
		indexFile.close();
		indexFile.clear();
		indexFile.open("indexfile.bin", ios::out | ios::binary);
		return false;
	}
	else
		return true;
}

void readIfile(fstream &indexFile, arptIndex &iContainer, set<arptIndex> &Index, int &RRN)
{
	//pre-condition: index file, airport index, airport index set, RRN
	//post-condition:  read from index file and place information into set

	indexFile.close();
	indexFile.clear();
	indexFile.open("indexfile.bin", ios::in | ios::out | ios::binary);
	indexFile.read(reinterpret_cast<char *>(&iContainer), sizeof(arptIndex));

	while(indexFile && !indexFile.eof())
	{
		Index.insert(iContainer);
		int tempRRN;
		tempRRN = iContainer.RRN;
		if(tempRRN > RRN - 1) //determine next RRN number
			RRN = tempRRN + 1;
		indexFile.read(reinterpret_cast<char *>(&iContainer), sizeof(arptIndex));
	}
	indexFile.close();
	indexFile.clear();
}

void deleteAirport(set<arptIndex> &Index, fstream &mfile)
{
	//pre-condition: airport index set, main file
	//post-condition:  if airport exist, delete airport from main file by placing * in
	//in the first byte of the record.  Delete airport from set.

	const int MAX_ID = 4;
	char id[MAX_ID];
	arptIndex tempIndex;
	Airport tempAirport;
	IndexFile::iterator findID;

	cout << endl << "Enter the id of the airport you wish to delete." << endl << endl;
	setID(id, MAX_ID);
	tempIndex.setID(id);

	findID = Index.find(tempIndex);
	if(findID != Index.end())
	{
		mfile.seekp(0);
		tempAirport.setID("*");
		mfile.seekp((findID->RRN) * sizeof(Airport));
		mfile.write(reinterpret_cast<const char *>(&tempAirport), sizeof(Airport));
		cout << endl << findID->id << " airport has been deleted." << endl << endl;
		Index.erase(findID);
	}
	else
		cout <<"Airport not found." << endl << endl;
}

void displayAirport(set<arptIndex> &Index, fstream &mfile)
{
	//pre-condition: airport index set, main file
	//post-condition:  if airport exist, display airport from main file

	const int MAX_ID = 4;
	char id[MAX_ID];
	arptIndex tempIndex;
	Airport tempAirport;
	IndexFile::iterator findID;

	cout << endl << "Enter the id of the airport you wish to display." << endl << endl;
	setID(id, MAX_ID);
	tempIndex.setID(id);

	findID = Index.find(tempIndex);
	if(findID != Index.end())
	{
		mfile.seekg(0);
		mfile.seekg((findID->RRN) * sizeof(Airport));
		mfile.read(reinterpret_cast<char *>(&tempAirport), sizeof(Airport));
		Header();
		cout << tempAirport << endl << endl;
	}
	else
		cout <<"Airport not found." << endl << endl;
}

void displayAirports(set<arptIndex> &Index, fstream &mfile)
{
	//pre-condition: airport index set, main file
	//post-condition:  display all airports on main file

	Airport tempAirport;

	Header();

	for(IndexFile::const_iterator iter = Index.begin(); iter != Index.end(); iter++)
	{
		mfile.seekg(0);
		mfile.seekg((iter->RRN) * sizeof(Airport));
		mfile.read(reinterpret_cast<char *>(&tempAirport), sizeof(Airport));
		cout << tempAirport << endl;
	}
	cout << endl;
}

void changeRunwayNumber(set<arptIndex> &Index, fstream &mfile)
{
	//pre-condition: airport index set, main file
	//post-condition:  change runway number for an airport and update main file

	const int MAX_ID = 4;
	char id[MAX_ID];
	int newRunway, tempRunway;
	arptIndex tempIndex;
	Airport tempAirport;
	IndexFile::iterator findID;

	cout << endl << "Enter the id of the airport you wish to change." << endl << endl;
	setID(id, MAX_ID);
	tempIndex.setID(id);

	findID = Index.find(tempIndex);
	if(findID != Index.end())
	{
		mfile.seekg(0);
		mfile.seekg((findID->RRN) * sizeof(Airport));
		mfile.read(reinterpret_cast<char *>(&tempAirport), sizeof(Airport));
		tempRunway = tempAirport.getRunway();
		setRunway(newRunway);
		tempAirport.setRunway(newRunway);

		mfile.seekp(0);
		mfile.seekp((findID->RRN) * sizeof(Airport));
		mfile.write(reinterpret_cast<const char *>(&tempAirport), sizeof(Airport));
		cout << endl << "Airport runway number has been changed from " << tempRunway << " to " << newRunway << '.' << endl << endl;
	}
	else
		cout <<"Airport not found." << endl << endl;
}