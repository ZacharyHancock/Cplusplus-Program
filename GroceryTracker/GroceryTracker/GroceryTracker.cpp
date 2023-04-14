/*
	Author: Zachary J. Hancock
	File: GroceryTracker.cpp
	Date: 04-12-2023
	Purpose: To read in an input file with a list of groceries and output a menu for user to get outputs based on selection
*/

#include <map>
#include <iostream>
#include <iomanip>
#include <map>
#include <fstream>
using namespace std;

// Declared functions for use
void displayMenu();
int getSelection();
void processSelection(int);
void printOptionOne();
void printOptionTwo();
void printOptionThree();

// Declared global variables
map<string, int> groceries;
const int SENTINEL = 4;

int main() {

	ifstream inputFile;
	string item;
	
	// Opens input file and checks if it failed to open or not then adds each item into the groceries map then closes input stream
	inputFile.open("GroceryList.txt");
	if (inputFile.fail()) {
		cout << "Error in file" << endl;
		return 1;
	}
	while (inputFile >> item) {

		if (groceries.count(item)) {
			groceries[item]++;
		}
		else {
			groceries.emplace(item, 1);
		}
	}
	inputFile.close();

	// Opens output file then outputs the list of groceries that was taken into the groceries map to a file named frequency.dat then closes the file
	ofstream outputFile ("frequency.dat");
	for (auto product : groceries) {
		outputFile << product.first << " " << product.second << endl;
	}
	outputFile.close();

	
	int selection = 0; // Used to take in user input to pass into processSelection
	// Do while continues until the selection equals the exit criteria
	do {
		displayMenu();
		selection = getSelection();
		processSelection(selection);
	} while (selection != SENTINEL);




}

// Functions purpose is to output a menu to prompt the users inputs
void displayMenu()
{
	cout << "Enter 1 to search for a specific item." << endl;
	cout << "Enter 2 to output a numerical list of all items." << endl;
	cout << "Enter 3 to output a histogram of all items" << endl;
	cout << "Enter " << SENTINEL << " to exit the program" << endl;
}


// returns input validated user input
// Purpose is to get the users input and validated it as an integer and a valid input and then return the selection if valid
int getSelection()
{
	int selection = 0;
	bool needSelection = true;

	// Do while runs until needSelection reads fales when selection is within the bounds of 1 and the SENTINEL which is 4 in this case
	do {
		cout << "Enter your menu selection 1 to " << SENTINEL << ": ";
		cin >> selection;
		if (cin.fail()) { 
			cin.clear();  // clear and ignore used to reset the stream so the terminal doesnt constantly read in a fail infinitely
			cin.ignore(100, '\n');
			cout << endl << "You must input an integer" << endl;
			continue;
		}
		cout << endl;
		needSelection = ((selection < 1) || (selection > SENTINEL));
		if (needSelection) {
			cout << "Invalid input - valid are 1 to " << SENTINEL << endl;
		}
	} while (needSelection);
	return selection;
}

// Purpose is to provide a switch branch that takes in the user selection then goes to the appropiate case for the user input
// 1 = select item and output its quantity
// 2 = output list with numerical quantity
// 3 = output histogram
// 4 = exit program
void processSelection(int selection)
{
	switch (selection){
	case 1:
		printOptionOne();
		break;
	case 2:
		printOptionTwo();
		break;
	case 3:
		printOptionThree();
		break;
	case 4:
		cout << "Thank you for using the Corner Grocer Tracker." << endl;
		break;		
	}
}

// Purpose is to output the Name of the users given item with its quantity
void printOptionOne()
{
	cout << "Enter the name of your item: ";  // Prompts user to enter a product name and read it into a string variable
	string selection;
	cin >> selection;
	map<string, int>::iterator it; // iterator used to store the groceries map key that the user selected
	it = groceries.find(selection);

	// If branch is in invalid entry
	// Else branch is a valid entry thus outputting the number of the selected item
	if (it == groceries.end()) {
		cout << "Item not available / Invalid Input" << endl << endl;
	}		
	else {
		cout << "There are " << it->second << " " << it->first << endl << endl;
	}
}

// Purpose is to output the list of items in the groceries map wiht the numerical quantity next to it
void printOptionTwo() {
	// For loop runs through each key of the groceries map and then gets its first and second to output 
	for (auto product : groceries) {
		cout << product.first << " " << product.second << endl;
	}
	cout << endl;
}

// Purpose is to output the list of items in a histogram
void printOptionThree()
{
	// For loop runs through each key of the groceries map and then output the name of the product the nested for loop outputs the number of asteriskts equal to the number of product.second
	for (auto product : groceries) {
		cout << right << setw(11) << product.first << " ";
		for (int i = 0; i < product.second; ++i) {
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;
}
