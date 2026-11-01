#include "storage.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

namespace {

const char DELIM = '|';
const string ROOMS_FILE = "rooms.txt";
const string GUESTS_FILE = "guests.txt";
const string RESERVATIONS_FILE = "reservations.txt";
const string ACCOUNTS_FILE = "accounts.txt";

// the delimiter must never appear inside a saved text field
string clean(string text){
    for(char& c : text){
        if(c == DELIM){
            c = '/';
        }
    }
    return text;
}

vector<string> split(const string& line){
    vector<string> parts;
    string part;
    stringstream ss(line);
    while(getline(ss, part, DELIM)){
        parts.push_back(part);
    }
    if(!line.empty() && line.back() == DELIM){
        parts.push_back("");
    }
    return parts;
}

bool saveRooms(const vector<Room>& rooms){
    ofstream out(ROOMS_FILE);
    if(!out){
        return false;
    }
    for(const Room& room : rooms){
        out << room.number << DELIM
            << static_cast<int>(room.type) << DELIM
            << room.pricePerNightCents << DELIM
            << room.capacity << DELIM
            << room.floor << DELIM
            << static_cast<int>(room.status) << "\n";
    }
    return true;
}

bool saveGuests(const vector<Guest>& guests){
    ofstream out(GUESTS_FILE);
    if(!out){
        return false;
    }
    for(const Guest& guest : guests){
        out << guest.id << DELIM
            << clean(guest.name) << DELIM
            << clean(guest.phone) << DELIM
            << clean(guest.email) << DELIM
            << clean(guest.passportId) << "\n";
    }
    return true;
}

bool saveReservations(const vector<Reservation>& reservations){
    ofstream out(RESERVATIONS_FILE);
    if(!out){
        return false;
    }
    for(const Reservation& reservation : reservations){
        out << clean(reservation.bookingId) << DELIM
            << reservation.roomNumber << DELIM
            << clean(reservation.guestName) << DELIM
            << clean(reservation.checkedInDate) << DELIM
            << clean(reservation.checkOutDate) << DELIM
            << static_cast<int>(reservation.status) << DELIM
            << reservation.guestId << "\n";
    }
    return true;
}

} // namespace

bool loadRooms(vector<Room>& rooms){
    ifstream in(ROOMS_FILE);
    if(!in){
        return false;
    }

    rooms.clear();
    string line;
    while(getline(in, line)){
        if(line.empty()){
            continue;
        }
        vector<string> fields = split(line);
        if(fields.size() != 6){
            continue;
        }
        try{
            int type = stoi(fields[1]);
            int status = stoi(fields[5]);
            if(type < 0 || type > 2 || status < 0 || status > 2){
                continue;
            }
            Room room;
            room.number = stoi(fields[0]);
            room.type = static_cast<RoomType>(type);
            room.pricePerNightCents = stoi(fields[2]);
            room.capacity = stoi(fields[3]);
            room.floor = stoi(fields[4]);
            room.status = static_cast<RoomStatus>(status);
            rooms.push_back(room);
        }catch(const exception&){
            continue; // skip a damaged line
        }
    }
    return true;
}

bool loadGuests(vector<Guest>& guests){
    ifstream in(GUESTS_FILE);
    if(!in){
        return false;
    }

    guests.clear();
    string line;
    while(getline(in, line)){
        if(line.empty()){
            continue;
        }
        vector<string> fields = split(line);
        if(fields.size() != 5){
            continue;
        }
        try{
            Guest guest;
            guest.id = stoi(fields[0]);
            guest.name = fields[1];
            guest.phone = fields[2];
            guest.email = fields[3];
            guest.passportId = fields[4];
            guests.push_back(guest);
        }catch(const exception&){
            continue;
        }
    }
    return true;
}

bool loadReservations(vector<Reservation>& reservations){
    ifstream in(RESERVATIONS_FILE);
    if(!in){
        return false;
    }

    reservations.clear();
    string line;
    while(getline(in, line)){
        if(line.empty()){
            continue;
        }
        vector<string> fields = split(line);
        // older files have 6 fields (no guestId); newer files have 7
        if(fields.size() != 6 && fields.size() != 7){
            continue;
        }
        try{
            int status = stoi(fields[5]);
            if(status < 0 || status > 3){
                continue;
            }
            Reservation reservation;
            reservation.bookingId = fields[0];
            reservation.roomNumber = stoi(fields[1]);
            reservation.guestName = fields[2];
            reservation.checkedInDate = fields[3];
            reservation.checkOutDate = fields[4];
            reservation.status = static_cast<ReservationStatus>(status);
            if(fields.size() == 7){
                reservation.guestId = stoi(fields[6]);
            }
            reservations.push_back(reservation);
        }catch(const exception&){
            continue;
        }
    }
    return true;
}

bool loadAccounts(vector<Account>& accounts){
    ifstream in(ACCOUNTS_FILE);
    if(!in){
        return false;
    }

    accounts.clear();
    string line;
    while(getline(in, line)){
        if(line.empty()){
            continue;
        }
        vector<string> fields = split(line);
        if(fields.size() != 3){
            continue;
        }
        try{
            Account account;
            account.username = fields[0];
            account.password = fields[1];
            account.guestId = stoi(fields[2]);
            accounts.push_back(account);
        }catch(const exception&){
            continue;
        }
    }
    return true;
}

bool saveAccounts(const vector<Account>& accounts){
    ofstream out(ACCOUNTS_FILE);
    if(!out){
        cerr << "Warning: could not save accounts to file.\n";
        return false;
    }
    for(const Account& account : accounts){
        out << clean(account.username) << DELIM
            << clean(account.password) << DELIM
            << account.guestId << "\n";
    }
    return true;
}

bool saveAll(const vector<Room>& rooms,
             const vector<Guest>& guests,
             const vector<Reservation>& reservations){
    bool ok = true;
    ok = saveRooms(rooms) && ok;
    ok = saveGuests(guests) && ok;
    ok = saveReservations(reservations) && ok;

    if(!ok){
        cerr << "Warning: could not save data to file.\n";
    }
    return ok;
}