#include "guest.h"
#include "../input_utils.h"

#include <iostream>

using namespace std;

// add guest function
void addGuest(vector<Guest>& guests){
    // continue from the highest existing ID so IDs stay unique after loading from file
    int maxId = 0;
    for(const Guest& guest : guests){
        if(guest.id > maxId){
            maxId = guest.id;
        }
    }

    Guest newGuest;
    newGuest.id = maxId + 1;

    cout << "Guest Name: ";
    getline(cin >> ws, newGuest.name);

    cout << "Enter Guest Phone Number: ";
    cin >> newGuest.phone;

    cout << "Enter Guest Email Address: ";
    cin >> newGuest.email;

    cout << "Enter Guest Passport ID: ";
    cin >> newGuest.passportId;

    guests.push_back(newGuest);

    cout << "Guest Added Successfully! (ID: " << newGuest.id << ")\n";
}

// list guests function
void listGuests(const vector<Guest>& guests){
    if(guests.empty()){
        cout << "No Guests Found.\n";
        return;
    }
    for(const Guest& guest : guests){
        cout << "Name: " << guest.name
             << " | ID: " << guest.id
             << " | Phone: " << guest.phone
             << " | Email: " << guest.email
             << " | Passport: " << guest.passportId
             << "\n";
    }
}

// search guest function
void searchGuest(const vector<Guest>& guests){
    string searchName;
    cout << "Run a search on guest name: ";
    getline(cin >> ws, searchName);

    bool found = false;
    for(const Guest& guest : guests){
        if (guest.name == searchName){
            found = true;
            cout << "Name: " << guest.name
                 << " | ID: " << guest.id
                 << " | Phone: " << guest.phone
                 << " | Email: " << guest.email
                 << " | Passport: " << guest.passportId
                 << "\n";
        }
    }
    if(!found){
        cout << "Guest Not Found.\n";
    }
}

// find a guest by ID
const Guest* findGuestById(const vector<Guest>& guests, int id){
    for(const Guest& guest : guests){
        if(guest.id == id){
            return &guest;
        }
    }
    return nullptr;
}

// guest management menu
void guestManagementMenu(vector<Guest>& guests){
    bool running = true;

    while(running){
        cout << "\n=== Guest Management ===\n"
             << "1. Add Guest\n"
             << "2. View Guests\n"
             << "3. Search Guest\n"
             << "4. Back\n";

        int choice = readMenuChoice("Select: ", 1, 4);
        switch (choice)
        {
        case 1:
            addGuest(guests);
            break;
        case 2:
            listGuests(guests);
            break;
        case 3:
            searchGuest(guests);
            break;
        case 4:
            running = false;
            break;
        default:
            cout << "Unknown";
            break;
        }
    }
}