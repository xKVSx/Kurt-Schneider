#include <iostream>
#include <iomanip>
#include <cstring>
#include "Runway.h"
#include "Airport.h"

using namespace std;

int getValidInt();
void program_intro();
void getMenuOption();
void getSubMenuOption();
void changeAirportInfo(Airport *a[], const int MAX_ARRAY);
Airport *setAirportInfo();
void changeAirportName(Airport *a[], const int MAX_ARRAY);
void changeAirportNum(Airport *a[], const int MAX_ARRAY);
void changeAirportLength(Airport *a[], const int MAX_ARRAY);
void setID(char *id, const int MAX_ID);
void setName(char *name, const int MAX_NAME);
void setNum(char *number, const int MAX_NUM);
int setLength();
void displayAirports(Airport *a[], const int MAX_ARRAY);

int main()
{
	// Declaration and initialization of variables
	int menu_option;
	const int MAX_ARRAY = 25;
	int index = 0;
	Airport *airportArray[MAX_ARRAY] = {0};

	program_intro();				// Display the program's purpose
	cout << endl;  

		do {
		// Display the menu and get the menu option
		getMenuOption();
		menu_option = getValidInt();
		
		switch (menu_option) 
		{
			case 1:	// Enter information for an airport
				if(index < MAX_ARRAY)
				{
					airportArray[index] = setAirportInfo();
					index++;
					cout << "Airport stored in list." << endl << endl;
				}
				else
					cout << "Airport list is full." << endl;
				break;
			case 2:	// Change airport information
				if(index == 0)
					cout << "Airport list is empty." << endl;
				else
					changeAirportInfo(airportArray, MAX_ARRAY);
				break;
			case 3:	// Display the list of airports
				if(index == 0)
					cout << "List is empty." << endl;
				else
				{
					displayAirports(airportArray, MAX_ARRAY);
				}
				break;
			case 4:	// Exit program
				cout << endl << "Menu option 4 chosen" << endl;
				break;
				default:  // Invalid menu option
					cout << "Invalid menu option.  Please re-enter." << endl;
					break;
		}  // end switch statement
	} while (menu_option != 4);	// end do-while loop

	return 0;
}

void program_intro()
{
	//pre-condition: none.
	//post-condition: display the purpose of the program.

	cout << "The program will maintain a list of a maximum of 25 airports" << endl;
	cout << "by an airport identifier, airport name, and runway number. " << endl;
}

void getMenuOption()
{
	//pre-condition: none.
	//post-condition:  display main menu options.

	cout << "Press 1 to enter information for an airport." << endl;
	cout << "Press 2 to change an airport's information." << endl;
	cout << "Press 3 to display the list of airports." << endl;
	cout << "Press 4 to exit." << endl << endl;
	cout << ":";
}

void getSubMenuOption()
{
	//pre-condtion: none.
	//post-condition: display sub-menu options.

	cout << "Press 1 to change the airport name." << endl;
	cout << "Press 2 to change the runway number." << endl;
	cout << "Press 3 to change the runway length." << endl;
	cout << "Press 4 to return to main menu." << endl << endl;
	cout << ":";
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

void changeAirportInfo(Airport *a[], const int MAX_ARRAY)
{
	char sub_menu_option;

	do {
		getSubMenuOption();
		sub_menu_option = getValidInt();
		switch (sub_menu_option) 
		{
			case 1:	// Change airport indentifier
				changeAirportName(a, MAX_ARRAY);
				break;
			case 2:	// Change runway number
				changeAirportNum(a, MAX_ARRAY);
				break;
			case 3: // Change runway length
				changeAirportLength(a, MAX_ARRAY);
				break;
			case 4:	// Return to main menu
				break;
				default:  // Invalid menu option
					cout << "Invalid menu option.  Please re-enter." << endl;
					break;
		}  // end switch statement
	} while (sub_menu_option != 4);
}

Airport *setAirportInfo()
{
	//pre-condition: none.
	//post-condition: creates, sets, and returns an airport.

	Airport *airpt;
	const int MAX_ID = 4;
	const int MAX_NAME = 26;
	const int MAX_NUM = 4;
	char id[MAX_ID];
	char name[MAX_NAME];
	char number[MAX_NUM];
	int length = 0;

	setID(id, MAX_ID);
	setName(name, MAX_NAME);
	setNum(number, MAX_NUM);
	length = setLength();
	airpt = new Airport(id, name, number, length);

	return airpt;
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

void displayAirports(Airport *a[], const int MAX_ARRAY)
{
	//pre-condition: list of airports
	//post-condition: displays the list

	int i = 0;

	cout << setw(4) << "ID" << setw(15) << "Name" << setw(24) << "Number" << setw(10) << "Length" << endl;
	cout <<"______________________________________________________" << endl;

	while(i < MAX_ARRAY && a[i] != NULL)
	{
			cout << i + 1 << " " << a[i] << endl;
			i++;
	}

	cout << endl;
}

void changeAirportName(Airport *a[], const int MAX_ARRAY)
{
	//pre-condition:  list of airports.
	//post-condition:  prompts user to change the name of an airport.  If the airport exists, change the name.

	int option;
	const int MAX_NAME = 26;
	char name[MAX_NAME];

	displayAirports(a, MAX_ARRAY);
	cout << "Choose the airport you would like to change:";
	option = getValidInt();
	
	if(a[option - 1] == NULL || option > MAX_ARRAY || option <= 0)
		cout << "No such airport." << endl;
	else
	{
		setName(name, MAX_NAME);
		a[option - 1]->setName(name);
	}
}

void changeAirportNum(Airport *a[], const int MAX_ARRAY)
{
	//pre-condition:  list of airports.
	//post-condition:  prompts user to change the airport number.  If the airport exists, change the number.

	int option;
	const int MAX_NUM = 4;
	char number[MAX_NUM];

	displayAirports(a, MAX_ARRAY);
	cout << "Choose the airport you would like to change:";
	option = getValidInt();
	
	if(a[option - 1] == NULL || option > MAX_ARRAY || option <= 0)
		cout << "No such airport." << endl;
	else
	{
		setNum(number, MAX_NUM);
		a[option - 1]->setNum(number);
	}
}

void changeAirportLength(Airport *a[], const int MAX_ARRAY)
{
	//pre-condition:  list of airports.
	//post-condition:  prompts user to change the length of an airport.  If the airport exists, change the length.

	int option;
	int length;

	displayAirports(a, MAX_ARRAY);
	cout << "Choose the airport you would like to change:";
	option = getValidInt();
	
	if(a[option - 1] == NULL || option > MAX_ARRAY || option <= 0)
		cout << "No such airport." << endl;
	else
	{
		length = setLength();
		a[option - 1]->setLength(length);
	}
}





