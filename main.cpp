#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
using namespace std;


//Room type and structure

enum class RoomType {Single, Double, Suite};
enum class RoomStatus {Available, Occupied, Reserved};

struct Room {
    int number{};
    RoomType type{RoomType::Single};
    int pricePerNightCents{};
    int capacity{};
    int floor{};
    RoomStatus status{RoomStatus::Available};
};


// function to show room type
string roomTypeToString(RoomType type){
    switch (type)
    {
    case RoomType::Single:
        return "Single";
        break;
    case RoomType::Double:
        return "Double";
        break;
    case RoomType::Suite:
        return "Suite";
    default:
        return "Unknown";
    }
}

string roomStatusToString(RoomStatus status){
    switch (status)
    {
    case RoomStatus::Available:
        return "Available";
    case RoomStatus::Occupied:
        return "Occupied";
    case RoomStatus::Reserved:
        return "Reserved";
    default:
        return "Unkown";
    }
}

// function to list all rooms
void listRooms(const vector<Room>& rooms){
    if (rooms.empty()){
        cout << "No Rooms have been added yet.\n";
        return;
    }

    for (const Room& room: rooms){ // same as for(int i=0; i<rooms.size(); i++)
        cout << "Room " << room.number
             << " | Type: " << roomTypeToString(room.type)
             << " | Status: " << roomStatusToString(room.status)
             << " | Floor: " << room.floor
             << " | Capacity: " << room.capacity
             << " | Price per night: $"
             << fixed << setprecision(2)
             << room.pricePerNightCents / 100.0
             << "\n";
    }
}

// structure for guest profile
struct Guest{
    int id{};
    string name;
    string phone;
    string email;
    string passportId;
};


// read for option selection_input
int readMenuChoice(const string & prompt, int minimum, int maximum){
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
//show guest menu 
int showGuestMenu(){
    cout << "Please select any of the following options you want to perform: "
         << "\n1. Guest Management"
         << "\n2. Reservations"
         << "\n3. Logout\n";

    return readMenuChoice("Select: ", 1, 3);
}
//show admin menu
int showAdminMenu(){
    cout << "Please select any of the following options you want to perform: "
         << "\n1. Room Managment"
         << "\n2. Guest Management"
         << "\n3. Reservation"
         << "\n4. Check in and Check out"
         << "\n5. Logout\n";
    return readMenuChoice("Select: ", 1, 5);
}

// check if room number exist function
bool roomNumberExists(const vector<Room>& rooms, int number){
    for (const Room& room : rooms){
        if (room.number == number){
            return true;
        }
    }
    return false;
}


// add room function
bool addRoom(vector<Room>& rooms, const Room& room){
    if (room.number <= 0 || room.pricePerNightCents <= 0 || room.capacity <=0){
        return false;
    }
    if (roomNumberExists(rooms, room.number)){
        return false;
    }
    rooms.push_back(room);
    return true;
}


// add room function menu
void addRoomMenu(vector<Room>& rooms){
    Room newRoom;

    cout << "Room Number: ";
    cin >> newRoom.number;

    if(roomNumberExists(rooms, newRoom.number)){
        cout << "Room already exists\n";
        return;
    }

    cout << "Please select any of the following options you want to perform: "
         << "\n1. Single"
         << "\n2. Double"
         << "\n3. Suite\n";

    int roomTypeChoice = readMenuChoice("select: ", 1,3);
    switch(roomTypeChoice){
        case 1: 
            newRoom.type = RoomType::Single;
            break;
        case 2:
            newRoom.type = RoomType::Double;
            break;
        case 3: 
            newRoom.type = RoomType::Suite;
            break;
        default: 
            cout << "Invalid option please try again!" << endl;
            break;
    }

    cout << "Capacity: ";
    cin >> newRoom.capacity;

    cout << "Floor: ";
    cin >> newRoom.floor;

    double price;
    
    cout << "Please enter the price (in USD): ";
    cin >> price;

    newRoom.pricePerNightCents = static_cast<int>(price*100);

    if(addRoom(rooms, newRoom)){
        cout << "Room added successfully\n";
    }else{
        cout << "Failed to add room\n";
    }
}

// edit room function
void editRoom(vector<Room> & rooms){
    int roomNumber;
    
    cout << "Enter Room Number to Edit: ";
    cin >> roomNumber;

    for(Room& room: rooms){
        if(room.number == roomNumber){
            cout << "New Capacity: ";
            cin >> room.capacity;

            cout << "New Floor: ";
            cin >> room.floor;

            cout << "Room Updated!\n";
            return;
        }
    }

    cout << "Room Note Found!\n";
}

// delete room function
void deleteRoom(vector<Room>& rooms){
    int roomNumber;
    cout << "Please Enter a room number to delete: ";
    cin >> roomNumber;

    for(size_t i =0; i < rooms.size(); i++){
        if(rooms[i].number == roomNumber){
            rooms.erase(rooms.begin() + i);
            cout << "Room Deleted!\n";
            return;
        }
    }
    cout << "Room Not Found!\n";
}

//add guest function
void addGuest(vector<Guest>& guests){
    Guest newGuest;
    cout << "Guest Name: ";
    getline (cin >> ws, newGuest.name);

    cout << "Enter Guest Phnome Number: ";
    cin >> newGuest.phone;

    cout << "Enter Guest Email Address: ";
    cin >> newGuest.email;

    cout << "Enter Guest Passport ID: ";
    cin >> newGuest.passportId;

    cout << "Guest Added Successfully!\n";

    guests.push_back(newGuest);
}

//list guests function
void listGuests(const vector<Guest>& guests){
    if(guests.empty()){
        cout << "No Guests Found.\n";
        return;
    }
    for(const Guest& guest : guests){
        cout << "Name " << guest.name
             << " | ID: " << guest.id
             << " | Phone: " << guest.phone
             << " | Email: " << guest.email
             << " | Passport: " << guest.passportId
             << "\n";
    }
}

//search guest function
void searchGuest(const vector<Guest>& guests){
    string searchName;
    cout << "Run a search on guest name: ";
    cin >> searchName;
    bool found = false;
    for(const Guest& guest : guests){
        if (guest.name == searchName){
            found = true;
            cout << "Name: " << guest.name
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

// reservation class enum
enum class ReservationStatus{
    Reserved,
    CheckedIn,
    CheckedOut,
    Cancelled
};

// reservation struct
struct Reservation{
    string bookingId;
    int roomNumber;
    string guestName;
    string checkedInDate;
    string checkOutDate;
    ReservationStatus status;
};

//generate booking ID function
string generateBookingId(){
    static int nextId = 1001;
    string bookingId = "BK" + to_string(nextId);
    nextId++;
    return bookingId;
}

string reservationStatusToString(ReservationStatus status){
    switch (status)
    {
    case ReservationStatus::Reserved:
        return "Reserved";
    case ReservationStatus::CheckedIn:
        return "Checked In";
    case ReservationStatus::CheckedOut:
        return "Checked Out";
    case ReservationStatus::Cancelled:
        return "Cancelled";
    default:
        return "Unknown";
    }
}

void bookRoom(vector<Reservation>& reservations, vector<Room> & rooms){
    Reservation newReservation;
    cout << "Guest name: ";
    cin >> newReservation.guestName;
    
    cout << "Room Number: ";
    cin >> newReservation.roomNumber;
    bool found = false;

    for(Room& room : rooms){
        if(room.number == newReservation.roomNumber){
            found = true;

            if (room.status != RoomStatus::Available){
                cout << "Room is not available!\n";
                return;
            }

            cout << "Check-In Date: ";
            cin >> newReservation.checkedInDate;

            cout << "Check-out Date:";
            cin >> newReservation.checkOutDate;

            newReservation.bookingId = generateBookingId();

            newReservation.status = ReservationStatus::Reserved;

            room.status = RoomStatus::Reserved;

            reservations.push_back(newReservation);

            cout << "Reservation Created!\n";
            return;
        }
    }

    if(!found){
        cout << "Room Not found!\n";
    }
}

// list all reservation
void listReservations(const vector<Reservation>& reservations){
    if(reservations.empty()){
    cout << "No Reservations Found.\n";
    return;}
    for(const Reservation& reservation:reservations){
        cout << "\n=====================\n"
             << "Booking ID: " << reservation.bookingId
             << " | Name: " << reservation.guestName
             << " | Room: " << reservation.roomNumber
             << "\nCheck-In: " << reservation.checkedInDate << "\n"
             << "\nCheck-Out: " << reservation.checkOutDate << "\n"
             << "\nStatus: " << reservationStatusToString(reservation.status)
             << "\n=====================\n";
    }
}

void cancelReservation(vector<Reservation>& reservations, vector<Room>&rooms){
    string bookingId;
    cout << "Please Enter your booking ID: ";
    cin >> bookingId;

    bool found = false;

    for (Reservation& reservation:reservations){

        if(reservation.bookingId == bookingId){
            if(reservation.status == ReservationStatus::Cancelled){
                cout << "Reservation already cancelled.\n";
                return;
            }
            reservation.status = ReservationStatus::Cancelled;
            for(Room& room:rooms){
                if(room.number == reservation.roomNumber){
                    room.status = RoomStatus::Available;
                    break;
                }
            }

            cout << "Reservation Cancelled!\n";

            found = true;
            break;;
        }
    }
    if(!found){
        cout << "Booking ID not found.\n";
    }
}

//modify Reservation
void modifyReservation(vector<Reservation>& reservations){
    string bookingId;
    cout << "Enter Booking ID: ";
    cin >> bookingId;
    bool found = false;

    for (Reservation& reservation:reservations){
        if(reservation.bookingId == bookingId){
            found = true;
            cout << "New Check-In Date: ";
            cin >> reservation.checkedInDate;

            cout << "New Check-Out Date: ";
            cin >> reservation.checkOutDate;

            cout << "Reservation Updated!\n";
            break;
        }
        if(!found){
            cout << "Booking ID Not Found!\n";
        }
    }
}

void filterRoomsByStatus(const vector<Room>& rooms){
    cout << "\n1. Available";
    cout << "\n2 Occupied";
    cout << "\n3. Reserved\n";

    int choice = readMenuChoice("Select: ", 1,3);

    RoomStatus target;

    switch (choice)
    {
    case 1:
        target = RoomStatus::Available;
        break;
    case 2:
        target = RoomStatus::Occupied;
        break;
    case 3:
        target = RoomStatus::Reserved;
        break;
    }

    for(const Room& room:rooms){
        if(room.status == target){
            cout << "Room " << room.number
                 << " | Type: "
                 << roomTypeToString(room.type)
                 << " | Floor: "
                 << room.floor
                 << "\n";
        }
    }
}

//Bill calculation function
double calculateBill(int roomPricePerNightCents, int nights){
    return (roomPricePerNightCents/100.0) * nights;
}

//CheckOut Function

void checkOut(vector<Reservation>& reservations, vector<Room>& rooms){
    string bookingId;

    cout << "Enter Booking ID: ";
    cin >> bookingId;

    for(Reservation& reservation:reservations){
        if(reservation.bookingId == bookingId){
            if(reservation.status != ReservationStatus::CheckedIn){
                cout << "Guest not checked in. \n";
                return;
            }
        int nights;
        cout << "Number of Nights: ";
        cin >> nights;

        reservation.status = ReservationStatus::CheckedOut;

        for(Room& room : rooms){
            if (room.number == reservation.roomNumber){
                double bill = calculateBill(room.pricePerNightCents, nights);
                room.status = RoomStatus::Available;

                cout << fixed << setprecision(2);

                cout << "Total Bill: $" << bill << "\n";
                break;
            }
        }

        cout << "Check-Out Successfully!\n";
        return;
        }
    }
    cout << "Booking ID Not Found!\n";
}

void checkIn(vector<Reservation>& reservations, vector<Room>& rooms){
    string bookingId;
    cout << "Please enter your booking ID: ";
    cin >> bookingId;

    for(Reservation& reservation:reservations){
        if(reservation.bookingId == bookingId){
            if(reservation.status != ReservationStatus::Reserved){
                cout << "Reservation cannot be checked in.\n";
                return;
            }
            reservation.status = ReservationStatus::CheckedIn;
            for(Room& room:rooms){
                if(room.number == reservation.roomNumber){
                    room.status = RoomStatus::Occupied;
                    break;
                }
            }
            cout << "Guest Checked In Successfully!\n";
            return;
        }
    }

    cout << "Booking ID Not Found!\n";
}

//reservation menu function

void reservationMenu(vector<Reservation>& reservations, vector<Room>& rooms){
    bool running = true;

    while(running){
        cout << "\n=== Reservation Menu ===\n";
        cout << "1. Book Room\n";
        cout << "2. View Reservations\n";
        cout << "3. Modify Reservation\n";
        cout << "4. Cancel Reservation\n";
        cout << "5. Back\n"; 

        int choice = readMenuChoice("Select: ", 1,5);
        switch(choice){
            case 1: 
                bookRoom(reservations, rooms);
                break;
            case 2: 
                listReservations(reservations);
                break;
            case 3:
                modifyReservation(reservations);
                break;
            case 4: 
                cancelReservation(reservations, rooms);
                break;
            case 5:
                running = false;
                break;
            default:
                cout << "Unknown";
                break;
        }
    }
}

//CheckInOut Menu

void checkInOutMenu(vector<Reservation>& reservations, vector<Room>& rooms){
    bool running = true;

    while(running){
        cout << "\n=== Check In/Out Menu ===\n";
        cout << "1. Check In\n";
        cout << "2. Check Out\n";
        cout << "3. Back\n";

        int choice = readMenuChoice("Select: ", 1,3);
        
        switch (choice)
        {
        case 1:
            checkIn(reservations, rooms);
            break;
        case 2:
            checkOut(reservations, rooms);
            break;
        case 3: 
            running = false;
            break;
        default:
            cout << "Unknown";
            break;
        }
    }
}



// RoomManagement menu function
void roomManangementMenu(vector<Room>& rooms){
    bool running = true;

    while(running){
        cout << "\n=== ROOM MANAGEMENT ===\n";
        cout << "1. Add Room\n";
        cout << "2. View Rooms\n";
        cout << "3. Edit Room\n";
        cout << "4. Delete Room\n";
        cout << "5. Filter Rooms\n";
        cout << "6. Back\n";

        int choice = readMenuChoice("Select: ", 1,6);

        switch(choice){
            case 1:
                addRoomMenu(rooms);
                break;
            case 2: 
                listRooms(rooms);
                break;
            case 3:
                editRoom(rooms);
                break;
            case 4:
                deleteRoom(rooms);
                break;
            case 5: 
                filterRoomsByStatus(rooms);
                break;
            case 6: 
                running = false;
                break;
            default:
                break;
        }
    }
}


// guest page for managementmenu
void guestManagementMenu(vector<Guest>& guests){
    
    bool running = true;

    while(running){
        cout << "\n=== Guest Management ===\n"
             << "1. Add Guest\n"
             << "2. View Guests\n"
             << "3. Search Guest\n"
             << "4. Back\n";

             int choice = readMenuChoice("Select: ", 1,4);
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

// runadminmenu function
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
                roomManangementMenu(rooms);
                break;
            case 2:
                cout << "\nGuest Management selected\n";
                guestManagementMenu(guests);
                break;
            case 3:
                cout << "\nReservation selected\n";
                reservationMenu(reservations, rooms);
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

    }
}

//run guest menu
void runGuestMenu(){
    bool running = true;
    while(running){
        int choice = showGuestMenu();
        if (choice == -1) {
            return;}
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
    string username_guest;
    string username_pass;
    string username_passretype;
    int option_type_user;
    vector<Room> rooms;
    rooms.push_back({101, RoomType::Single, 5000, 1, 1, RoomStatus::Available});
    rooms.push_back({201, RoomType::Double, 9000, 2, 2, RoomStatus::Available});
    vector<Guest> guests;
    vector<Reservation> reservations;

    cout << "\n --- Welcome to the Hotel Manangemt System --- \n" << endl;
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
            if(type_passw=="admin123" && type_usrname=="admin"){
                cout << "\nAccess Granted!\n" << endl;
                runAdminMenu(rooms, guests, reservations);}
            else{
                cout << "Invalid Username or Password. Please Try again!" << endl; 
                break;
            }
            break;
        case 2: { // Added curly brace to open a localized scope block
            cout << "\n--- Welcome To The Hotel Portal Page ---\n";
            cout << "Please Sign in with existing account or Sign up if you're a new user: 1. Sign in     2. Sign up" << endl;
            option_guest_account = readMenuChoice("Select: ", 1, 2);
            if(option_guest_account==-1){
                return 0;
            }
            switch(option_guest_account){
                case 2:
                    cout << "Choose a username: ";
                    cin >> username_guest;
                    do {
                        cout << "Please enter your password: ";
                        cin >> username_pass;

                        cout << "Please retype your password: ";
                        cin >> username_passretype;

                        if (username_pass != username_passretype) {
                            cout << "Passwords do not match. Please try again.\n";
                        }
                    } while (username_pass != username_passretype);

                    cout << "Passwords match. Account storage is not implemented yet.\n";
                    break;
                case 1:
                    cout << "Please Enter your username: ";
                    cin >> username_guest;
                    cout << "Please Enter your password: ";
                    cin >> username_pass;
                    break;
                default:
                    cout << "\nInvalid option to Proceed\n";
                    break;
            }
            runGuestMenu();   
            break;
        }
        default:
            cout << "\nInvalid option to Proceed, Please pick again\n";
            break;
    }
    return 0;
}