#include <iostream>
#include <fstream>
#include "Item.h"
#include <map>
#include <vector>

using namespace std;
/*
Andrew Wales
Module 7 assignment
01March2024
*/
int DisplayMainMenu() {
    int inputForDisplay;
    cout << "***********************************************************" << endl;
    cout << "***       Please select one of the options below!       ***" << endl;
    cout << "***      To see an Items inventory please enter 1.      ***" << endl;
    cout << "*** To see all items and their inventory count press 2. ***" << endl;
    cout << "***   To see all items in histographic form press 3.    ***" << endl;
    cout << "***        To exit the program please enter 4.          ***" << endl;
    cout << "***********************************************************" << endl;
    cin >> inputForDisplay;
    // Error handling for input that would render a bad selection.
    	while (inputForDisplay > 4 || inputForDisplay < 1) {
    		if (inputForDisplay > 4 || inputForDisplay < 1) {
    			cout << "Please make a valid selection of 1, 2, 3, or 4!" << endl;
    			cin >> inputForDisplay;
    		}
    	}
    return inputForDisplay;
}

void InputSelector(std::map<string, int> maps, int inputs) {
    // logic for input of 1
    if (inputs == 1) {
        string searchInput;
        cout << "Please enter item you wish to view!" << endl;
        cin >> searchInput;
        cout << searchInput << " " << maps.at(searchInput) << endl;
    }
    // logic for input of 2
    if (inputs == 2) {
        for (auto it = maps.begin(); it != maps.end(); it++) {
            cout << it->first << " " << it->second << endl;
        }
    }
    // logic for input of 3
    if (inputs == 3) {
        for (auto it = maps.begin(); it != maps.end(); it++) {
            int tempInt = it->second;
            string newString;
            for (int i = 0; i < tempInt; i++) {
                newString = newString + "+";
            }
            cout << it->first << " " << newString << endl;
        }
    }
}
int main() {
    ifstream inFS;   // Input file stream
    ofstream outFS;  // Output file stream
    map<string, int> ItemMap;
    string itemname; // File data
    vector<Item> items; // vector to temporarily store file data
    int displayReturn; // int value returned by display function

    // Open files
    cout << "Opening files." << endl;
    inFS.open("storeList.txt");
    outFS.open("frequency.dat");

    // Error handling for file openings
    if (!inFS.is_open()) {
        cout << "Could not open FahrenheitTemperature.txt file." << endl;
        return 1;
    }
    if (!outFS.is_open()) {
        cout << "Could not open the CelsiusTemperature.txt file." << endl;
        return 1;
    }
    inFS >> itemname;
    // Loop through file and use that data to populate a vector that we can use to populate map with correct data.
    while (!inFS.fail()) {
    
        Item newItem(itemname);
        items.push_back(newItem);
        inFS >> itemname;
    }

    // Error handling in case something went wrong while reading the file
    if (!inFS.eof()) {
        cout << "Input failure before reaching end of file." << endl;
    }

    // Close input file.
    inFS.close();
    
    // Loop through vector and set the data in the map
    for (int i = 0; i < items.size(); i++) {
        int itemCount = 0;
        // internal loop to get the item count
        for (int j = 0; j < items.size(); j++) {
            if (items.at(i).GetName() == items.at(j).GetName()) {
                itemCount = itemCount + 1;
            }
        }
        // perform map build
        ItemMap.emplace(items.at(i).GetName(), itemCount);
    }

    // Loop through the map and place each item in the new output file.
    for (auto it = ItemMap.begin(); it != ItemMap.end(); it++) {
        outFS << it->first << " " << it->second << endl;
    }

    // Close out file.
    outFS.close();
    
    // call the display function and input selector functions for the user
    displayReturn = DisplayMainMenu();
    while (displayReturn != 4) {
        InputSelector(ItemMap, displayReturn);
        displayReturn = DisplayMainMenu();
    }
    cout << "Hope you have a great day!" << endl;
    return 0;
}