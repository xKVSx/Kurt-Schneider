#include <iostream>
#include <iomanip>
#include <cstring>
#include "Runway2.h"
#include "Airport2.h"
#include "NonToweredAirport.h"
#include "ToweredAirport.h"

using namespace std;

int getValidInt();
void program_intro();
void getMenuOption();
void getSubMenuOptionT();
void getSubMenuOptionNT();
Airport *setNonToweredAirportInfo();
Airport *setToweredAirportInfo();
void changeToweredAirportInfo(Airport *a[], const int INDEX);
void changeNonToweredAirportInfo(Airport *a[], const int INDEX);
void setID(char *id, const int MAX_ID);
void setName(char *name, const int MAX_NAME);
void setNum(char *number, const int MAX_NUM);
void setPIA(char *pia, const int MAX_PIA);  //for non-towered airports
int setLength();
double setFrequency(); //for towered airports
void displayAirports(Airport *a[], const int INDEX);
void displayToweredAirports(Airport *a[], const int INDEX, bool &tafound);
void displayNonToweredAirports(Airport *a[], const int INDEX, bool &ntafound);
void copyAirportList(Airport *a[], Airport *c[], const int INDEX);

int main()
{
	// Declaration and initialization of variables
	int menu_option;
	const int MAX_ARRAY = 3;
	int index = 0;
	bool copylist = false;
	Airport *airportArray[MAX_ARRAY] = {0};
	Airport *copyArray[MAX_ARRAY] = {0};

	program_intro();				// Display the program's purpose
	cout << endl;  

		do {
		// Display the menu and get the menu option
		getMenuOption();
		menu_option = getValidInt();
		
		switch (menu_option) 
		{
			case 1:	// Enter information for a towered airport
				if(index < MAX_ARRAY)
				{
					airportArray[index] = setToweredAirportInfo();
					index++;
					cout << endl << "Airport stored in list." << endl << endl;
				}
				else
					cout << "Airport list is full." << endl;
				break;
			case 2:  //Enter information for a non-towered airport
				if(index < MAX_ARRAY)
				{
					airportArray[index] = setNonToweredAirportInfo();
					index++;
					cout << endl << "Airport stored in list." << endl << endl;
				}
				else
					cout << "Airport list is full." << endl;
				break;
			case 3:	// Change towered airport information
				if(index == 0)
					cout << "Airport list is empty." << endl << endl;
				else
					changeToweredAirportInfo(airportArray, index);
				break;
			case 4: //Change non-towered airport information
				if(index == 0)
					cout << "Airport list is empty." << endl << endl;
				else
					changeNonToweredAirportInfo(airportArray, index);
				break;
			case 5:	// Display the list of airports
				if(index == 0)
					cout << "Airport List is empty." << endl << endl;
				else
					displayAirports(airportArray, index);
				break;
			case 6: // Copy list of airports
				if(index == 0)
					cout <<"Airport list is empty." << endl << endl;
				else
				{   copylist = true;
					copyAirportList(airportArray, copyArray, index);
					cout <<"Airporst list has been copied." << endl << endl;
				}
				break;
			case 7://Display the copies list
				if(index == 0)
					cout <<"Airport list is empty." << endl << endl;
				else
				{	if(copylist)
						displayAirports(copyArray, MAX_ARRAY);
					else
						cout <<"Airport list has not been copied." << endl << endl;
				}
				break;
			case 8:	// Exit program
				break;
				default:  // Invalid menu option
					cout << "Invalid menu option.  Please re-enter." << endl;
					break;
		}  // end switch statement
	} while (menu_option != 8);	// end do-while loop

	return 0;
}

void program_intro()
{
	//pre-condition: none.
	//post-condition: display the purpose of the program.

	cout << "The program will maintain a list of a maximum of 25 airports.  The airports" << endl;
	cout << "will either be towered or non-towered.  Each airport will have a unique" << endl;
	cout << "identifier, name, and runway number. The towered airports will contain a" << endl;
	cout << "primary instrument approach and the non-towered airports will contain a CTAF"  << endl;
	cout << "frequency." << endl;
	cout << "******************************************************************************" << endl;
}

void getMenuOption()
{
	//pre-condition: none.
	//post-condition:  display main menu options.

	cout << "Press 1 to enter information for a towered airport." << endl;
	cout << "Press 2 to enter information for a non-towered airport." << endl;
	cout << "Press 3 to change a towered airport's information." << endl;
	cout << "Press 4 to change a non-towered airport's information." << endl;
	cout << "Press 5 to display the list of airports." << endl;
	cout << "Press 6 to copy the list of airports." << endl;
	cout << "Press 7 to display the copies list of airports." << endl;
	cout << "Press 8 to exit." << endl << endl;
	cout << "Enter menu option: ";
}

void getSubMenuOptionT()
{
	//pre-condtion: none.
	//post-condition: display sub-menu options.

	cout << "Press 1 to change the airport name." << endl;
	cout << "Press 2 to change the runway number." << endl;
	cout << "Press 3 to change the runway length." << endl;
	cout << "Press 4 to change the primary instrument approach." << endl;
	cout << "Press 5 to return to main menu." << endl << endl;
	cout << "Enter menu option: ";
}

void getSubMenuOptionNT()
{
	//pre-condtion: none.
	//post-condition: display sub-menu options.

	cout << "Press 1 to change the airport name." << endl;
	cout << "Press 2 to change the runway number." << endl;
	cout << "Press 3 to change the runway length." << endl;
	cout << "Press 4 to change the frequency." << endl;
	cout << "Press 5 to return to main menu." << endl << endl;
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

Airport *setNonToweredAirportInfo()
{
	//pre-condition: none.
	//post-condition: creates, sets, and returns a towered airport.

	Airport *ntaipt;
	const int MAX_ID = 4;
	const int MAX_NAME = 26;
	const int MAX_NUM = 4;
	char id[MAX_ID];
	char name[MAX_NAME];
	char number[MAX_NUM];
	int length = 0;
	double frequency = 0.0;

	frequency = setFrequency();
	setID(id, MAX_ID);
	setName(name, MAX_NAME);
	setNum(number, MAX_NUM);
	length = setLength();
	
	ntaipt = new NonToweredAirport(id, name, number, length, frequency);

	return ntaipt;
}

Airport *setToweredAirportInfo()
{
	//pre-condition: none.
	//post-condition: creates, sets, and returns a non towered airport.

	Airport *tairpt;
	const int MAX_PIA = 6;
	char pia[MAX_PIA];
	const int MAX_ID = 4;
	const int MAX_NAME = 26;
	const int MAX_NUM = 4;
	char id[MAX_ID];
	char name[MAX_NAME];
	char number[MAX_NUM];
	int length = 0;

	setPIA(pia, MAX_PIA);
	setID(id, MAX_ID);
	setName(name, MAX_NAME);
	setNum(number, MAX_NUM);
	length = setLength();

	tairpt = new ToweredAirport(id, name, number, length, pia);

	return tairpt;
}

void setPIA(char *pia, const int MAX_PIA)
{
	//pre-condition: prompts user for primary instrument approach
	//post-condition: sets the primary instrument approach

	const int MAX_BUFFER = 80;
	char buffer[MAX_BUFFER];

	cout << endl << "Enter towered airport primary instrument approach: ";
	cin.getline(buffer, MAX_BUFFER);

	while((strlen(buffer)) >= MAX_PIA)
	{
		cout << "Towered airport approach is too long - please re-enter: ";
		cin.getline(buffer, MAX_BUFFER);
	}

	strcpy(pia, buffer);
}

double setFrequency()
{
	//pre-condition: prompts user for frequency
	//post-condition: returns frequency.

	const int MAX = 80;
	char buffer[MAX];
	double d;

	cout << endl << "Enter the frequency: ";
	cin.getline(buffer, MAX); //prompt user for input

	while((strlen(buffer)) != strspn(buffer, ".0123456789"))
	{
		cout << "Invalid option - please re-enter: ";
		cin.getline(buffer, MAX);
	}

	d = atof(buffer);

	return d;
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

void setNum(char *number, const int MAX_NUM)
{
	//pre-condition:  prompt user for the airport number
	//post-condition:  if airport number is valid, set number.  if airport number is too large, re-prompt user.

	const int MAX_BUFFER = 80;
	char buffer[MAX_BUFFER];

	cout << "Enter airport number: ";
	cin.getline(buffer, MAX_BUFFER);

	while((strlen(buffer)) >= MAX_NUM)
	{
		cout << "Airport number is too long - please re-enter: ";
		cin.getline(buffer, MAX_BUFFER);
	}

	strcpy(number, buffer);
}

int setLength()
{
	//pre-condition: none
	//post-condition:  if length is valid, return length.  if not, re-prompt user.

	const int MAX = 50;
	char buffer[MAX];
	int length;

	cout << "Enter the runway length: ";
	cin.getline(buffer, MAX);

	while((strlen(buffer)) != strspn(buffer, "0123456789"))
	{
		cout << "Invalid length - please re-enter: ";
		cin.getline(buffer, MAX);
	}

	length = atoi(buffer);

	return length;
}

void changeToweredAirportInfo(Airport *a[], const int INDEX)
{
	//pre-condition: Airport list and the number of airports in the list.
	//post-condition: change info for towered airports only

	int aport; //the airport to be changed
	int option; //what needs to be changed
	const int MAX_PIA = 6;
	char pia[MAX_PIA];
	const int MAX_NAME = 26;
	const int MAX_NUM = 4;
	char name[MAX_NAME];
	char number[MAX_NUM];
	int length = 0;
	bool TAfound = false;

	displayToweredAirports(a, INDEX, TAfound);

	if(TAfound == true)
	{
		cout << "Please enter the airport you would like to change: ";
		aport = getValidInt();

		while(aport <= 0 || aport > INDEX)
		{
			cout << endl << "Invalid option - please re-enter: ";
			aport = getValidInt();
		}

		ToweredAirport *Towerpointer = dynamic_cast < ToweredAirport * >(a[aport - 1]);

		while(Towerpointer == NULL)
		{
			cout << endl << "You did not enter a towered airport - please re-enter: ";
			aport = getValidInt();

			while(aport <= 0 || aport > INDEX)
			{
				cout << endl << "Invalid option - please re-enter: ";
				aport = getValidInt();
			}

			Towerpointer = dynamic_cast < ToweredAirport * >(a[aport - 1]);
		}

		if(Towerpointer != NULL)
		{
			cout << endl;
			getSubMenuOptionT();

			do {
				option = getValidInt();

				switch (option) 
				{
					case 1:	// Change airport name
						cout << endl;
						setName(name, MAX_NAME);
						Towerpointer->setName(name);
						cout << "Enter menu option: ";
						break;
					case 2:	// Change runway number
						cout << endl;
						setNum(number, MAX_NUM);
						Towerpointer->setNum(number);
						cout << "Enter menu option: ";
						break;
					case 3: // Change runway length
						cout << endl;
						length = setLength();
						Towerpointer->setLength(length);
						cout << "Enter menu option: ";
						break;
					case 4: //changePIA
						cout << endl;
						setPIA(pia, MAX_PIA);
						Towerpointer->setApproach(pia);
						cout << "Enter menu option: ";
						break;
					case 5:
						cout << endl;
						break; //exist sub-menu
							default:  // Invalid menu option
							cout << "Invalid menu option.  Please re-enter.";
							break;
							// end switch statement
					}
				} while (option != 5);
			}	
	}
}

void changeNonToweredAirportInfo(Airport *a[], const int INDEX)
{
	//pre-condition: Airport list and the number of airports in the list.
	//post-condition: change info for non towered airports only

	int aport; //the airport to be changed
	int option; //what needs to be changed
	double frequency = 0.0;
	const int MAX_NAME = 26;
	const int MAX_NUM = 4;
	char name[MAX_NAME];
	char number[MAX_NUM];
	int length = 0;
	bool NTAfound = false;

	displayNonToweredAirports(a, INDEX, NTAfound);

	if(NTAfound == true)
	{
		cout << "Please enter the airport you would like to change: ";
		aport = getValidInt();

		while(aport <= 0 || aport > INDEX)
		{
			cout << endl << "Invalid option - please re-enter: ";
			aport = getValidInt();
		}

		NonToweredAirport *NonTowerpointer = dynamic_cast < NonToweredAirport * >(a[aport - 1]);

		while(NonTowerpointer == NULL)
		{
			cout << endl << "You did not enter a non towered airport - please re-enter: ";
			aport = getValidInt();

			while(aport <= 0 || aport > INDEX)
			{
				cout << endl << "Invalid option - please re-enter: ";
				aport = getValidInt();
			}

			NonTowerpointer = dynamic_cast < NonToweredAirport * >(a[aport - 1]);
		}

		if(NonTowerpointer != NULL)
		{
			cout << endl;
			getSubMenuOptionNT();

			do {
				option = getValidInt();

				switch (option) 
				{
					case 1:	// Change airport name
						cout << endl;
						setName(name, MAX_NAME);
						NonTowerpointer->setName(name);
						cout << "Enter menu option: ";
						break;
					case 2:	// Change runway number
						cout << endl;
						setNum(number, MAX_NUM);
						NonTowerpointer->setNum(number);
						cout << "Enter menu option: ";
						break;
					case 3: // Change runway length
						cout << endl;
						length = setLength();
						NonTowerpointer->setLength(length);
						cout << "Enter menu option: ";
						break;
					case 4:
						// Change frequency
						cout << endl;
						frequency = setFrequency();
						NonTowerpointer->setFrequency(frequency);
						cout << "Enter menu option: ";
						break;
					case 5:
						cout << endl;
						break; //exist sub-menu
						default:  // Invalid menu option
							cout << "Invalid menu option.  Please re-enter.";
							break;
							// end switch statement
				}
			} while (option != 5);
		}
		else
			cout <<"You did not enter a Non-towered Airport.";
	}
}

void displayAirports(Airport *a[], const int INDEX)
{
	//pre-condition: list of airports
	//post-condition: displays the list

	cout << setw(4) << "ID" << setw(7) << "Name" << right << setw(28) << "Number" << setw(10) << "Length" << setw(23) << "Approach/Frequency" << endl;
	cout <<"_________________________________________________________________" << endl;

	for(int i = 0; i < INDEX; i++)
			cout << i + 1 << " " << *a[i];

	cout << endl << endl;
}

void displayToweredAirports(Airport *a[], const int INDEX, bool &tafound)
{
	//pre-condition: list of airports
	//post-condition: displays the list

	int header = 0;

	for(int i = 0; i < INDEX; i++)
	{
		ToweredAirport *Towerpointer = dynamic_cast < ToweredAirport * >(a[i]);

		if(Towerpointer != NULL)
		{
			tafound = true;

			if(header == 0)
			{
				cout << setw(4) << "ID" << setw(7) << "Name" << right << setw(28) << "Number" << setw(10) << "Length"; 
				cout << setw(10) << "Approach" << endl;
				cout <<"_________________________________________________________________" << endl;
				header++;
			}
		
			cout << i + 1 << " " << *a[i];
		}
	}

	if(tafound == false)
		cout <<"There are no towered airports.";

	cout << endl << endl;
}

void displayNonToweredAirports(Airport *a[], const int INDEX, bool &NTAfound)
{
	//pre-condition: list of airports
	//post-condition: displays the list

	int header = 0;

	for(int i = 0; i < INDEX; i++)
	{
		NonToweredAirport *NonTowerpointer = dynamic_cast < NonToweredAirport * >(a[i]);

		if(NonTowerpointer != NULL)
		{
			NTAfound = true;

			if(header == 0)
			{
				cout << setw(4) << "ID" << setw(7) << "Name" << right << setw(28) << "Number" << setw(10) << "Length" << setw(10); 
				cout << "Frequency" << endl;
				cout <<"_________________________________________________________________" << endl;
				header++;
			}

			cout << i + 1 << " " << *a[i];
		}
	}

	if(NTAfound == false)
		cout <<"There are no non towered airports.";

	cout << endl << endl;
}

void copyAirportList(Airport *a[], Airport *c[], const int INDEX)
{
	//pre-condition: Airport list, copy of airport list and the number of airports in the list.
	//post-condition: copy the orginal airport list into copyArray.

	for(int i = 0; i < INDEX; i++)
	{
		ToweredAirport *Towerpointer = dynamic_cast < ToweredAirport * >(a[i]);
		NonToweredAirport *NonTowerpointer = dynamic_cast < NonToweredAirport * >(a[i]);

		if(Towerpointer != NULL)
			c[i] = new ToweredAirport(*Towerpointer);
		else
			c[i] = new NonToweredAirport(*NonTowerpointer);
	}
}

