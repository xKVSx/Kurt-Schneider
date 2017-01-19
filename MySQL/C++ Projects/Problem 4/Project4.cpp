#include <iostream>
#include <iomanip>
#include <cstring>
#include "Airport4.h"

using namespace std;

int getValidInt();
int getValidInt2();
void program_intro();
void getMenuOption();
void Header();
void setID(char *id, const int MAX_ID);
void setName(char *name, const int MAX_NAME);
void setintArray(int intArray1[], int intArray2[], const int &size);
void displayList(Airport list[], const int &size, const char sortType);
Airport setAirportInfo();
template<typename T> int binarySearch(const T list[], const int &size, const T &item);
template<typename T> void insertionSort(T list[], const int &size);
template<typename T> void displayList(T list[], const int &size, const char sortType);
template<typename T> void mergeSort(T list[], const int &low, const int &high);
template<typename T> void merge(T list[], const int &low, const int &middle1, const int &middle2, const int &high);
template<typename T> void copyArray(T list[], T listCopy[], const int &size);

int main()
{
	// Declaration and initialization of variables
	int menu_option;
	int size = 5;
	int intArray1[5] = {0}, intArray2[5] = {0};
	Airport airptArray1[7], airptArray2[7];

	program_intro(); // Display the program's purpose
	cout << endl;  

		do {
		// Display the menu and get the menu option
		getMenuOption();
		menu_option = getValidInt();
		
		switch (menu_option) 
		{
			case 1:	// 
				cout << endl;
				setintArray(intArray1, intArray2, size);
				displayList(intArray1, size, 'i'); //insertion sort
				displayList(intArray2, size, 'm'); // merge sort
				break;
			case 2:  //
				if(intArray1[0] == NULL)
					cout <<"Integer array is empty." << endl << endl;
				else 
				{
					int integer;
					cout << endl << "Enter the integer you wish to search for: ";
					integer = getValidInt2();

					if(binarySearch(intArray1, size, integer) == -1)
						cout << endl << "Integer not found in array using insertion sort." << endl;
					else
						cout << endl << integer << " is located at position " << binarySearch(intArray1, size, integer) 
							 <<" in the array used for insertion sort." << endl;
					if(binarySearch(intArray2, size, integer) == -1)
						cout << endl << "Integer not found in array using merge sort." << endl << endl;
					else
						cout << endl << integer << " is located at position " << binarySearch(intArray2, size, integer) 
							 <<" in the array used for merge sort." << endl << endl;
				}
				break;
			case 3:	//
				cout << "Enter seven airports. " << endl << endl;

				for(int index = 0; index < size; index++)
					airptArray1[index] = setAirportInfo();

				copyArray(airptArray1, airptArray2, size);
				insertionSort(airptArray1, size);
				cout << endl;
				displayList(airptArray1, size, 'i');
				mergeSort(airptArray2, 0, size - 1);
				displayList(airptArray2, size, 'm');
				break;
			case 4: //
				if(strcmp(airptArray1[0].getID(), "") == 0)
					cout <<"Airport array is empty." << endl << endl;
				else
				{
					Airport temp;
					char tempID[4];
					setID(tempID, 4);
					temp.setID(tempID);

					if(binarySearch(airptArray1, size, temp) == -1)
						cout << endl << "Airport not found in the array using insertion sort." << endl;
					else
						cout << endl << temp.getID() << " is located at position " << binarySearch(airptArray1, size, temp) 
							 <<" in the array using insertion sort." << endl;
					if(binarySearch(airptArray2, size, temp) == -1)
						cout << endl << "Airport not found in the array using merge sort." << endl << endl;
					else
						cout << endl << temp.getID() << " is located at position " << binarySearch(airptArray2, size, temp) 
							 <<" in the array using merge sort." << endl << endl;
				}
				break;
			case 5:
				break;
				default:  // Invalid menu option
					cout << "Invalid menu option.  Please re-enter." << endl;
					break;
		}  // end switch statement
	} while (menu_option != 5);	// end do-while loop

	return 0;
}

void program_intro()
{
	//pre-condition: none.
	//post-condition: display the purpose of the program.

	cout << "The program will contain a list of airports in alphabetical order according" << endl; 
	cout << "to a unqiue identifier and a list of integers in ascending order." << endl;
	cout << "***************************************************************************" << endl;
}

void getMenuOption()
{
	//pre-condition: none.
	//post-condition:  display main menu options.

	cout << "Press 1 to enter 7 integers into an array and display in sorted order." << endl;
	cout << "Press 2 to search array for integer and display the location index." << endl;
	cout << "Press 3 to enter 7 airports into an array and display in sorted order." << endl;
	cout << "Press 4 to search array for airports and display the location index." << endl;
	cout << "Press 5 to exit." << endl << endl;
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

int getValidInt2()
{
	//pre-condition: prompt user input
	//post-condition:  if input is valid, return input as integer.  If not valid, re-prompt user for input.

	const int MAX = 80;
	char buffer[MAX];
	int i;

	cin.getline(buffer, MAX); //prompt user for input

	while((strlen(buffer)) != strspn(buffer, "-0123456789"))
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
	//pre-condition:  none
	//post-condition: display airport header

	cout << left;
	cout << setw(5) << "ID" << setw(7) << "Name" << endl;
	cout <<"___________________________________" << endl;
}
	
void setintArray(int intArray1[], int intArray2[], const int &size)
{
	//pre-condition:  two integer arrays and the size of both arrays
	//post-condition: check for valid inputs.  if valid, place into first array.  copy first array into second array.
	                //use insertion sort on the first array and merge sort on the second array.

	for(int i = 0; i < size; i++)
	{
		cout << "integer " << i + 1 <<": ";
		intArray1[i] = getValidInt2();
	}

	copyArray(intArray1, intArray2, size);
	insertionSort(intArray1, size); //sort first array using insertion sort
	mergeSort(intArray2, 0, size - 1); // sort second array using merge sort

	cout << endl;
}

template<typename T> 
void displayList(T list[], const int &size, const char sortType)
{
	//pre-condition:  array, size of array and sort type (insertion or merge)
	//post-condition: display array

	if(sortType == 'i')
		cout << "Sorted list using insertion sort: ";
	else
		cout << "Sorted list using merge sort: ";

	for(int i = 0; i < size; i++)
		cout << list[i] << (i < size - 1 ? ", " : "");

	cout << endl << endl;
}

void displayList(Airport list[], const int &size, const char sortType)
{
	//pre-condition:  airport array, size of airport array and sort type (insertion or merge)
	//post-condition: display airport array

	if(sortType == 'i')
		cout << "Sorted list using insertion sort: ";
	else
		cout << "Sorted list using merge sort: ";

	cout << endl << endl;

	Header();

	for(int i = 0; i < size; i++)
		cout << list[i] << endl;

	cout << endl << endl;
}

template<typename T> 
void copyArray(T list[], T listCopy[], const int &size)
{
	//pre-condition:  array 1, array 2 and their sizes
	//post-condition: copy array list into array listCopy

	for(int i = 0; i < size; i++)
		listCopy[i] = list[i];
}

template<typename T>
int binarySearch(const T list[], const int &size, const T &item)
{
	//pre-condition:  array, size of array and item to be searched for
	//post-condition:  if item is found, return the position of the item in the array.  if not found, return -1

	int first = 0;
	int last = size - 1;
	int mid;

	bool found = false;

	while(first <= last && !found)
	{
		mid = (first + last) / 2;

		if(list[mid] == item)
			found = true;
		else if(list[mid] > item)
			last = mid - 1;
		else
			first = mid + 1;
	}

	if(found)
		return mid;
	else
		return -1;
}

template<typename T> 
void insertionSort(T list[], const int &size)
{
	//pre-condition:  array and size of array
	//post-condition: sort the array in ascending order

	for(int fOutOfOrder = 1; fOutOfOrder < size; fOutOfOrder++)
		if(list[fOutOfOrder] < list[fOutOfOrder - 1])
		{
			T temp = list[fOutOfOrder];
			int location = fOutOfOrder;

			do
			{
				list[location] = list[location - 1];
				location--;
			}
			while(location > 0 && list[location - 1] > temp);

			list[location] = temp;
		}
}

template<typename T> 
void mergeSort(T list[], const int &low, const int &high)
{
	//pre-condition:  low is the beginning of the array, high is the end of the array
	//post-condition: sort array in ascending order

	if((high - low) >= 1)
	{
		int middle1 = (low + high) / 2; //upper bound of first half of array
		int middle2 = middle1 + 1;      //lower bound of second half of array

		mergeSort(list, low, middle1);  //first half of array
		mergeSort(list, middle2, high); //second half of array

		merge(list, low, middle1, middle2, high);
	}
}

template<typename T> 
void merge(T list[], const int &low, const int &middle1, const int &middle2, const int &high)
{
	//pre-condition:  orginal array, and upper and lower bounds for two sub-arrays
	//post-condition: sort sub-arrays and merge into orignal array
	
	int leftIndex = low;
	int rightIndex = middle2;
	int combinedIndex = low;
	T mergedArray[5]; //size of orginal array

	while(leftIndex <= middle1 && rightIndex <= high)
	{
		if(list[leftIndex] <= list[rightIndex])
			mergedArray[combinedIndex++] = list[leftIndex++];
		else
			mergedArray[combinedIndex++] = list[rightIndex++];
	}

	if(leftIndex == middle2)
	{
		while(rightIndex <= high)
			mergedArray[combinedIndex++] = list[rightIndex++];
	}
	else
	{
		while(leftIndex <= middle1)
			mergedArray[combinedIndex++] = list[leftIndex++];
	}
		
	for(int i = low; i <= high; i++)
		list[i] = mergedArray[i];
}



