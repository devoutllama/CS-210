
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

bool quit = false;
struct ItemData {
	string itemName;    // hold the item name
	int count = 0; // hold the frequency
};

vector<ItemData> GetFrequencyDataFromFile(string fileName) {
	ifstream inFS;  // create an input file stream
	vector<ItemData> itemsData;  // create a vector to store item data
	ItemData currentData;   // create a structure to hold current item and count
	string currentLine;	// store the current line being read from file

	inFS.open(fileName, ios::in);    // open specified file
	if (!inFS.is_open()) {  // check if file could not be opened
		cout << "Could not open file: " << fileName << endl;
		return vector<ItemData> {}; // return an empty vector
	}

	while (!inFS.eof()) {   // read until end of file
		getline(inFS, currentLine);	// get the current line and store the contents

		if (!(currentLine == "")) {	// check if current line is not empty
			stringstream ss(currentLine);	// create a stringstream from the data in current line

			ss >> currentData.itemName;	// store the first value in the string stream (item name) into current data
			ss >> currentData.count;	// store the second value in the string stream (item frequency) into current data

			itemsData.push_back(currentData);    // add current data to vector
		}
	}

	inFS.close();   // close the file stream

	return itemsData;    // return the vector of items purchased
}


void PrintFrequencyList() {
	cout << "Frequency list:\n";
	vector<ItemData> data = GetFrequencyDataFromFile("frequency.dat");	// load the data from file and get a vector of data

	for (unsigned int i = 0; i < data.size(); ++i) {	// loop through each item's data
		cout << data.at(i).itemName << " " << data.at(i).count << endl;	// print the item name and frequency
	}
}

void PrintItemHistogram() {
	vector<ItemData> data = GetFrequencyDataFromFile("frequency.dat");	// load the data from file and get a vector of data

	for (unsigned int i = 0; i < data.size(); ++i) {	// loop through each item's data
		cout << data.at(i).itemName << " ";	// print the item name
		for (unsigned int j = 0; j < data.at(i).count; ++j) {	// loop for each item
			cout << "*";	// print an asterisk representing an item
		}
		cout << endl;
	}
}

void MenuSelection(string selection) {
	cout << endl;

	// Option 4: Exit application
	if (selection == "4") {
		quit = true;	// set global quit variable to true
		cout << "Exiting application..." << endl;	// display exit message
		return;
	}

	// Option 2: Print frequency of all items
	if (selection == "2") {
		cout << "Frequency for all items: " << endl;

		// call method to print frequency of all items
		//PrintItemHistogram();
		PrintFrequencyList();
		
		cout << endl;
		return;
	}

	// Option 1: Print frequency for specific item
	if (selection == "1") {
		string userInput;    // define a variable to hold item name to search for from user input

		cout << "Which item would you like to see a frequency for?:" << endl;
		cin.ignore();    // clear any existing input in cin buffer
		cin >> userInput;    // get item name from user

		// call method to get frequency of specific item
		vector<ItemData> data = GetFrequencyDataFromFile("frequency.dat");
		for (const auto& item : data) {
			if (item.itemName == userInput) {
				cout << item.itemName << ": " << item.count << endl;
				break;
			}
		}

		cout << endl;

		return;
	}

	// Option 3: Print histogram
	if (selection == "3") {
		cout << "Generating Histogram..." << endl;

		// call Python method to generate a frequency.dat file for a day's purchases
		//CallProcedure("GeneratePurchaseFrequencyReport");
		PrintItemHistogram();	// print the histogram based on data from frequency.dat

		cout << endl;
		return;
	}

	cout << "Please enter a valid selection..." << endl << endl;
}


//Prints the menu for the user, displaying the choices available to them.
void PrintMenu() {
	cout << "           Corner Grocer Sales History          " << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "1. Search for item" << endl;
	cout << "2. Display item frequency" << endl;
	cout << "3. Display histogram" << endl;
	cout << "4. Exit Application" << endl;
	cout << "Please enter your selection as a number 1-4:" << endl;
}

int main()
{
	string userSelection;	// holds the selection a user makes

	while (!quit) {	// loop while global application quit state is false
		PrintMenu();	// Print the application menu
		cin >> userSelection;	// get menu selection from user
		MenuSelection(userSelection);	// process the user's menu selection
	}
	//cout << "Current Directory: " << fs::current_path() << endl; 
	return 0;
}
