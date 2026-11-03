#include <iostream>
#include <string>
#include <vector>

#include "input_utils.h"
#include "Room Management/room.h"
#include "Guest Management/guest.h"
#include "Reservation System/reservation.h"
#include "Storage/storage.h"

using namespace std;

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123";
const int MAX_LOGIN_ATTEMPTS = 3;

// show admin menu
int showAdminMenu(){
    cout << "Please select any of the following options you want to perform: "
         << "\n1. Room Management"
         << "\n2. Guest Management"
         << "\n3. Reservation"
         << "\n4. Logout\n";
    return readMenuChoice("Select: ", 1, 4);
}

// run admin menu function
void runAdminMenu(vector<Room>& rooms, vector<Guest>& guests, vector<Reservation>& reservations){
    bool running = true;
    while(running){
        int choice = showAdminMenu();
        if (choice == -1){
            return;
        }
        switch(choice){
            case 1:
                cout << "\nRoom Management selected\n";
                roomManagementMenu(rooms);
                break;
            case 2:
                cout << "\nGuest Management selected\n";
                guestManagementMenu(guests);
                break;
            case 3:
                cout << "\nReservation selected\n";
                reservationMenu(reservations, rooms, guests);
                break;
            case 4:
                cout << "\nLogout successfully!\n";
                running = false;
                break;
            default:
                cout << "\nInvalid admin option\n";
                break;
        }

        // save after every action so data is not lost if the program closes suddenly
        saveAll(rooms, guests, reservations);
    }
}

int main(){
    vector<Room> rooms;
    vector<Guest> guests;
    vector<Reservation> reservations;

    if(!loadRooms(rooms)){
        // first run: no rooms file yet, so start with the sample rooms
        rooms.push_back({101, RoomType::Single, 5000, 1, 1, RoomStatus::Available});
        rooms.push_back({201, RoomType::Double, 9000, 2, 2, RoomStatus::Available});
    }
    loadGuests(guests);
    loadReservations(reservations);

    cout << "\n --- Welcome to the Hotel Management System --- \n" << endl;
    cout << " ---- Admin Login ---- \n" << endl;

    for(int attempt = 1; attempt <= MAX_LOGIN_ATTEMPTS; attempt++){
        string username;
        string password;

        cout << "Please enter your username: ";
        cin >> username;
        cout << "Please enter your password: ";
        cin >> password;
        if(!cin){
            return 0;
        }

        if(username == ADMIN_USERNAME && password == ADMIN_PASSWORD){
            cout << "\nAccess Granted!\n" << endl;
            runAdminMenu(rooms, guests, reservations);
            return 0;
        }

        cout << "Invalid Username or Password. Attempts left: "
             << MAX_LOGIN_ATTEMPTS - attempt << "\n";
    }

    cout << "Too many failed attempts. Goodbye!\n";
    return 0;
}