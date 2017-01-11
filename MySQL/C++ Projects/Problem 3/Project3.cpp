#include <iostream>
#include <iomanip>
#include <cstring>
#include <set>
#include <iterator>
#include <algorithm>
#include "Airport3.h"

using namespace std;

int getValidInt();
void program_intro();
void getMenuOption();
void Header();
void setID(char *id, const int MAX_ID);
void setName(char *name, const int MAX_NAME);
Airport SetAirportInfo();
template <typename T> void displayAirports(const set<T> &A);
template <typename T> void deleteAirport(set<T> &A);
template <typename T> void clearAirportList(set<T> &A);
template <typename T> void findAirportList(set<T> &A);
typedef set<Airport, less<Airport> > AirportSet;

int main()
{
	// Declaration and initialization of variables
	int menu_option;
	AirportSet Aset;
	pair<AirportSet::const_iterator, bool> dpl;  //pair to determine if airport was inserted

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
				dpl = Aset.insert(SetAirportInfo());

				if(dpl.second == true)
					cout << endl << "Airport stored in list." << endl << endl;
				else
					cout << endl << "Airport ID already exist.  Airport was not stored in list." << endl << endl;
				break;
			case 2:  //delete an airport from the list
				deleteAirport(Aset);
				break;
			case 3:	// locate and display a list
				findAirportList(Aset);
				break;
			case 4: //clear the list
				clearAirportList(Aset);
				break;
			case 5:	// display airports in ascending identifier order
				displayAirports(Aset);
				break;
			case 6:
				break;
				default:  // Invalid menu option
					cout << "Invalid menu option.  Please re-enter." << endl;
					break;
		}  // end switch statement
	} while (menu_option != 6);	// end do-while loop

	return 0;
}

void program_intro()
{
	//pre-condition: none.
	//post-condition: display the purpose of the program.

	cout << "The program will contain a list of airports in alphabetical order according" << endl; 
	cout << "to a unqiue identifier." << endl;
	cout << "***************************************************************************" << endl;
}

void getMenuOption()
{
	//pre-condition: none.
	//post-condition:  display main menu options.

	cout << "Press 1 to enter information for an airport." << endl;
	cout << "Press 2 to delete an airport form the list." << endl;
	cout << "Press 3 to locate and display an airport." << endl;
	cout << "Press 4 to clear the list of airports." << endl;
	cout << "Press 5 to display the list of airports." << endl;
	cout << "Press 6 to exit." << endl << endl;
	cout << "Enter menu option: ";
}

int getValidInt()
{
	//pre-condition: prompt user input
	//post-condition:  if input is valid, return input as integer.  If not valid, re-prompt user for input.

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

Airport SetAirportInfo()
{
	//pre-condition: none.
	//post-condition: creates, sets, and returns a towered airport.

	const int MAX_ID = 4;
	const int MAX_NAME = 26;
	char id[MAX_ID];
	char name[MAX_NAME];
	bool find = false;

	setID(id, MAX_ID);
	setName(name, MAX_NAME);
	Airport aprt(id, name);

	return aprt;
}

void setID(char *id, const int MAX_ID)
{
	//pre-condition:  prompt user for the airport id
	//post-condition:  if airport id is valid, set id.  if airport id is too large, re-prompt user.

	const int MAX_BUFFER = 80;
	char buffer[MAX_BUFFER];

	cout << "Enter airport ID: ";
	cin.getline(buffer, MAX_BUFFER);

	while((strlen(buffer)) >= MAX_ID)
	{
		cout << "ID is too long - please re-enter: ";
		cin.getline(buffer, MAX_BUFFER);
	}

	strcpy(id, buffer);
}

void setName(char *name, const int MAX_NAME)
{
	//pre-condition:  prompt user for airport name
	//post-condition:  if airport name is valid, set name.  if airport name is too large, re-prompt user.

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
	cout << right;
	cout << setw(4) << "ID" << setw(7) << "Name" << endl;
	cout <<"___________________________________" << endl;
}

template <typename T> void displayAirports(const set<T> &A)
{
	//pre-condition: list of airports
	//post-condition: displays the list

	AirportSet::const_iterator AirportTracer;
	int count = 1;

	if(A.empty())
		cout <<"Airport list is empty." << endl << endl;
	else
	{
		cout << endl;
		Header();

		for(AirportTracer = A.begin(); AirportTracer != A.end(); AirportTracer++)
			cout << count++ << " " << *AirportTracer << endl;

		cout << endl;
	}
}

template <typename T> void deleteAirport(set<T> &A)
{
	//pre-condition: list of airports
	//post-condition: deletes airport from list

	int option;
	bool found = false;
	AirportSet::iterator AirportLocate;
	AirportSet::const_iterator AirportTracer;

	if(A.empty())
		cout <<"Airport list is empty." << endl << endl;
	else
	{
		displayAirports(A);

		cout <<"Enter the airport you wish to delete: ";
		option = getValidInt();

		while(option > A.size() || option == 0)
		{
			cout << "No such airport - please re-enter: ";
			option = getValidInt();
		}

		AirportLocate = A.begin();

		for(int i = 1; i < option; i++) 
			AirportLocate++;

		for(AirportTracer = A.begin(); found == false;)
		{
			if(AirportTracer == AirportLocate)
			{
				found = true;
				A.erase(AirportLocate);
				cout <<"Airport has been deleted." << endl << endl;
			}
			else
				AirportTracer++;
		}
	}
}

template <typename T> void clearAirportList(set<T> &A)
{
	//pre-condition: list of airports
	//post-condition: clears airport list

	if(A.empty())
		cout <<"Airport list is empty." << endl << endl;
	else
	{
		A.clear();
		cout <<"Airport list has been cleared. " << endl << endl;
	}
}

template <typename T> void findAirportList(set<T> &A)
{
	//pre-condition: list of airports
	//post-condition: searches for airport by id.  If id is found, display airport.

	const int MAX_ID = 4;
	char id[MAX_ID];
	bool find = false;
	AirportSet::const_iterator AirportLocate;

	if(A.empty())
		cout <<"Airport list is empty." << endl << endl;
	else
	{
		cout << endl << "Search for airport by ID or press 'q' to quit. ";
		setID(id, MAX_ID);
		cout << endl;
		
		AirportLocate = A.begin();
		
		while(find != true)
		{
			if(strcmp(AirportLocate->getID(), id) == 0)
			{
				find = true; //airport found
				cout << endl;
				Header();
				cout << '1' << ' ' << *AirportLocate << endl << endl;
			}
			else
			{
				AirportLocate++;
				if(AirportLocate == A.end())
				{
					cout <<"Airport does not exit (press 'q' to quit). ";
					setID(id, MAX_ID);
					if(strcmp(id, "q") == 0)
					{
						find = true; //quit searching.  set find to true to stop search.
						cout << endl;
					}
					AirportLocate = A.begin();
				}
			}	
		}
	}
}
	

