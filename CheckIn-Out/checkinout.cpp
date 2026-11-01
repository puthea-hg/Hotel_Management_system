#include "checkinout.h"
#include "../input_utils.h"

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// bill calculation function
double calculateBill(int roomPricePerNightCents, int nights){
    return (roomPricePerNightCents / 100.0) * nights;
}

// check in function
void checkIn(vector<Reservation>& reservations, vector<Room>& rooms){
    string bookingId;
    cout << "Please enter your booking ID: ";
    cin >> bookingId;

    for(Reservation& reservation : reservations){
        if(reservation.bookingId == bookingId){
            if(reservation.status != ReservationStatus::Reserved){
                cout << "Reservation cannot be checked in.\n";
                return;
            }
            reservation.status = ReservationStatus::CheckedIn;
            for(Room& room : rooms){
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

// check out function
void checkOut(vector<Reservation>& reservations, vector<Room>& rooms){
    string bookingId;

    cout << "Enter Booking ID: ";
    cin >> bookingId;

    for(Reservation& reservation : reservations){
        if(reservation.bookingId == bookingId){
            if(reservation.status != ReservationStatus::CheckedIn){
                cout << "Guest not checked in.\n";
                return;
            }

            int nights;
            cout << "Number of Nights: ";
            cin >> nights;

            if(nights <= 0){
                cout << "Number of nights must be at least 1.\n";
                return;
            }

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

// check in/out menu
void checkInOutMenu(vector<Reservation>& reservations, vector<Room>& rooms){
    bool running = true;

    while(running){
        cout << "\n=== Check In/Out Menu ===\n";
        cout << "1. Check In\n";
        cout << "2. Check Out\n";
        cout << "3. Back\n";

        int choice = readMenuChoice("Select: ", 1, 3);

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