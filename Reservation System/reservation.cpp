#include "reservation.h"
#include "../input_utils.h"

#include <iostream>
#include <iomanip>

using namespace std;

// generate booking ID function
string generateBookingId(const vector<Reservation>& reservations){
    // continue from the highest existing booking number, e.g. BK1005 -> BK1006
    int maxId = 1000;
    for(const Reservation& reservation : reservations){
        if(reservation.bookingId.size() > 2){
            try{
                int number = stoi(reservation.bookingId.substr(2));
                if(number > maxId){
                    maxId = number;
                }
            }catch(const exception&){
                // ignore IDs that are not in the BK#### format
            }
        }
    }
    return "BK" + to_string(maxId + 1);
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

// book a room for a specific guest (used by admin booking and the guest portal)
void bookRoomForGuest(vector<Reservation>& reservations, vector<Room>& rooms, const Guest& guest){
    Reservation newReservation;
    newReservation.guestId = guest.id;
    newReservation.guestName = guest.name;

    cout << "Room Number: ";
    cin >> newReservation.roomNumber;

    for(Room& room : rooms){
        if(room.number == newReservation.roomNumber){

            if (room.status != RoomStatus::Available){
                cout << "Room is not available!\n";
                return;
            }

            cout << "Check-In Date: ";
            cin >> newReservation.checkedInDate;

            cout << "Check-out Date: ";
            cin >> newReservation.checkOutDate;

            newReservation.bookingId = generateBookingId(reservations);
            newReservation.status = ReservationStatus::Reserved;
            room.status = RoomStatus::Reserved;

            reservations.push_back(newReservation);

            cout << "Reservation Created! Booking ID: "
                 << newReservation.bookingId << "\n";
            return;
        }
    }

    cout << "Room Not found!\n";
}

// admin books a room: choose the guest by ID first
void bookRoom(vector<Reservation>& reservations, vector<Room>& rooms, const vector<Guest>& guests){
    if(guests.empty()){
        cout << "No guests registered yet. Add a guest in Guest Management first.\n";
        return;
    }

    int guestId{};
    cout << "Guest ID: ";
    cin >> guestId;

    const Guest* guest = findGuestById(guests, guestId);
    if(guest == nullptr){
        cout << "Guest ID not found. Add the guest in Guest Management first.\n";
        return;
    }

    cout << "Booking for " << guest->name << "\n";
    bookRoomForGuest(reservations, rooms, *guest);
}

// list all reservations
void listReservations(const vector<Reservation>& reservations){
    if(reservations.empty()){
        cout << "No Reservations Found.\n";
        return;
    }
    for(const Reservation& reservation : reservations){
        cout << "\n=====================\n"
             << "Booking ID: " << reservation.bookingId
             << " | Name: " << reservation.guestName
             << " | Guest ID: " << reservation.guestId
             << " | Room: " << reservation.roomNumber
             << "\nCheck-In: " << reservation.checkedInDate
             << "\nCheck-Out: " << reservation.checkOutDate
             << "\nStatus: " << reservationStatusToString(reservation.status)
             << "\n=====================\n";
    }
}

// cancel a reservation
void cancelReservation(vector<Reservation>& reservations, vector<Room>& rooms){
    string bookingId;
    cout << "Please Enter your booking ID: ";
    cin >> bookingId;

    for (Reservation& reservation : reservations){
        if(reservation.bookingId == bookingId){
            if(reservation.status == ReservationStatus::Cancelled){
                cout << "Reservation already cancelled.\n";
                return;
            }
            if(reservation.status != ReservationStatus::Reserved){
                cout << "Only reservations that are not yet checked in can be cancelled.\n";
                return;
            }

            reservation.status = ReservationStatus::Cancelled;
            for(Room& room : rooms){
                if(room.number == reservation.roomNumber){
                    room.status = RoomStatus::Available;
                    break;
                }
            }

            cout << "Reservation Cancelled!\n";
            return;
        }
    }

    cout << "Booking ID not found.\n";
}

// modify a reservation
void modifyReservation(vector<Reservation>& reservations){
    string bookingId;
    cout << "Enter Booking ID: ";
    cin >> bookingId;

    for (Reservation& reservation : reservations){
        if(reservation.bookingId == bookingId){
            cout << "New Check-In Date: ";
            cin >> reservation.checkedInDate;

            cout << "New Check-Out Date: ";
            cin >> reservation.checkOutDate;

            cout << "Reservation Updated!\n";
            return;
        }
    }

    cout << "Booking ID Not Found!\n";
}

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
                if(room.number == reservation.roomNumber){
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

// reservation menu function
void reservationMenu(vector<Reservation>& reservations, vector<Room>& rooms, const vector<Guest>& guests){
    bool running = true;

    while(running){
        cout << "\n=== Reservation Menu ===\n";
        cout << "1. Book Room\n";
        cout << "2. View Reservations\n";
        cout << "3. Modify Reservation\n";
        cout << "4. Cancel Reservation\n";
        cout << "5. Check In\n";
        cout << "6. Check Out\n";
        cout << "7. Back\n";

        int choice = readMenuChoice("Select: ", 1, 7);
        switch(choice){
            case 1:
                bookRoom(reservations, rooms, guests);
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
                checkIn(reservations, rooms);
                break;
            case 6:
                checkOut(reservations, rooms);
                break;
            case 7:
                running = false;
                break;
            default:
                cout << "Unknown";
                break;
        }
    }
}