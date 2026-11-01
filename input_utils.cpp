#include "input_utils.h"

#include <iostream>
#include <limits>

using namespace std;

// read for option selection_input
int readMenuChoice(const string& prompt, int minimum, int maximum){
    int choice{};
    while(true){
        cout << prompt;
        if (cin >> choice){
            if (choice >= minimum && choice <= maximum){
                return choice;
            }
            cout << "Please enter a choice from "
                 << minimum << " to " << maximum << ".\n";
        }else{
            if(cin.eof()){
                return -1;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number. \n";
        }
    }
}