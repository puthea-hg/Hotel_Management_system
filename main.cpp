#include <iostream>
#include <string>
#include <vector>

#include "input_utils.h"
#include "Room Management/room.h"
#include "Guest Management/guest.h"
#include "Reservation System/reservation.h"
#include "CheckIn-Out/checkinout.h"
#include "Account/account.h"
#include "Storage/storage.h"

using namespace std;

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123";

// show guest menu
int showGuestMenu(){
    cout << "Please select any of the following options you want to perform: "
         << "\n1. Guest Management"
         << "\n2. Reservations"
         << "\n3. Logout\n";

    return readMenuChoice("Select: ", 1, 3);
}

// show admin menu
int showAdminMenu(){
    cout << "Please select any of the following options you want to perform: "
         << "\n1. Room Management"
         << "\n2. Guest Management"
         << "\n3. Reservation"
         << "\n4. Check in and Check out"
         << "\n5. Logout\n";
    return readMenuChoice("Select: ", 1, 5);
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
                cout << "\nCheck in and Check out selected\n";
                checkInOutMenu(reservations, rooms);
                break;
            case 5:
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

// run guest menu
void runGuestMenu(){
    bool running = true;
    while(running){
        int choice = showGuestMenu();
        if (choice == -1) {
            return;
        }
        switch (choice){
            case 1:
                cout << "\nGuest Management\n";
                break;
            case 2:
                cout << "\nReservations\n";
                break;
            case 3:
                cout << "\nLogout successfully\n";
                running = false;
                break;
            default:
                cout << "\nInvalid guest option\n";
                break;
        }
    }
}

int main(){
    string type_usrname;
    string type_passw;
    int option_guest_account;
    int option_type_user;

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

    vector<Account> accounts;
    loadAccounts(accounts);

    cout << "\n --- Welcome to the Hotel Management System --- \n" << endl;
    cout << "Which type of user are you: 1.Admin     2.Guest" << endl;
    option_type_user = readMenuChoice("Select: ", 1, 2);
    if (option_type_user == -1) {
        return 0;
    }
    switch (option_type_user)
    {
        case 1:
            cout << "\n ---- Welcome to admin dashboard --- \n" << endl;
            cout << "Please enter your username: ";
            cin >> type_usrname;
            cout << "Please enter your password: ";
            cin >> type_passw;
            if(type_passw == ADMIN_PASSWORD && type_usrname == ADMIN_USERNAME){
                cout << "\nAccess Granted!\n" << endl;
                runAdminMenu(rooms, guests, reservations);
            }
            else{
                cout << "Invalid Username or Password. Please Try again!" << endl;
            }
            break;
        case 2: {
            cout << "\n--- Welcome To The Hotel Portal Page ---\n";
            cout << "Please Sign in with existing account or Sign up if you're a new user: 1. Sign in     2. Sign up" << endl;
            option_guest_account = readMenuChoice("Select: ", 1, 2);
            if(option_guest_account == -1){
                return 0;
            }
            int guestId = -1;
            if(option_guest_account == 2){
                if(registerAccount(accounts, guests)){
                    guestId = accounts.back().guestId;
                    saveAll(rooms, guests, reservations);
                    saveAccounts(accounts);
                }
            }else{
                guestId = signIn(accounts);
                if(guestId == -1){
                    cout << "Sign in failed. Please try again later.\n";
                }
            }

            if(guestId != -1){
                const Guest* guest = findGuestById(guests, guestId);
                if(guest != nullptr){
                    cout << "\nWelcome, " << guest->name << "!\n";
                }
                runGuestMenu();
            }
            break;
        }
        default:
            cout << "\nInvalid option to Proceed, Please pick again\n";
            break;
    }
    return 0;
}