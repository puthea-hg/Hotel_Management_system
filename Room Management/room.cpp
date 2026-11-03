#include "room.h"
#include "../input_utils.h"

#include <iostream>
#include <iomanip>

using namespace std;

// function to show room type
string roomTypeToString(RoomType type){
    switch (type)
    {
    case RoomType::Single:
        return "Single";
    case RoomType::Double:
        return "Double";
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
        return "Unknown";
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
             << room.pricePerNightDollars
             << "\n";
    }
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
    if (room.number <= 0 || room.pricePerNightDollars <= 0 || room.capacity <= 0){
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

    int roomTypeChoice = readMenuChoice("select: ", 1, 3);
    switch(roomTypeChoice){
        case 1:
            newRoom.type = RoomType::Single;
            newRoom.pricePerNightDollars = 50;
            break;
        case 2:
            newRoom.type = RoomType::Double;
            newRoom.pricePerNightDollars = 90;
            break;
        case 3:
            newRoom.type = RoomType::Suite;
            newRoom.pricePerNightDollars = 150;
            break;
        default:
            cout << "Invalid option please try again!" << endl;
            break;
    }

    cout << "Capacity: ";
    cin >> newRoom.capacity;

    cout << "Floor: ";
    cin >> newRoom.floor;

    if(addRoom(rooms, newRoom)){
        cout << "Room added successfully\n";
    }else{
        cout << "Failed to add room\n";
    }
}

// edit room function
void editRoom(vector<Room>& rooms){
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

    cout << "Room Not Found!\n";
}

// delete room function
void deleteRoom(vector<Room>& rooms){
    int roomNumber;
    cout << "Please Enter a room number to delete: ";
    cin >> roomNumber;

    for(size_t i = 0; i < rooms.size(); i++){
        if(rooms[i].number == roomNumber){
            rooms.erase(rooms.begin() + i);
            cout << "Room Deleted!\n";
            return;
        }
    }
    cout << "Room Not Found!\n";
}

// filter rooms by status
void filterRoomsByStatus(const vector<Room>& rooms){
    cout << "\n1. Available";
    cout << "\n2. Occupied";
    cout << "\n3. Reserved\n";

    int choice = readMenuChoice("Select: ", 1, 3);

    RoomStatus target = RoomStatus::Available;

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

    for(const Room& room : rooms){
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

// RoomManagement menu function
void roomManagementMenu(vector<Room>& rooms){
    bool running = true;

    while(running){
        cout << "\n=== ROOM MANAGEMENT ===\n";
        cout << "1. Add Room\n";
        cout << "2. View Rooms\n";
        cout << "3. Edit Room\n";
        cout << "4. Delete Room\n";
        cout << "5. Filter Rooms\n";
        cout << "6. Back\n";

        int choice = readMenuChoice("Select: ", 1, 6);

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