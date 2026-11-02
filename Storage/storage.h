#pragma once

#include <vector>

#include "../Room Management/room.h"
#include "../Guest Management/guest.h"
#include "../Reservation System/reservation.h"

// Each load function returns false if its file does not exist yet
// (e.g. the very first run). In that case the vector is left untouched.
bool loadRooms(std::vector<Room>& rooms);
bool loadGuests(std::vector<Guest>& guests);
bool loadReservations(std::vector<Reservation>& reservations);

// Saves rooms, guests and reservations. Returns false if any file
// could not be written.
bool saveAll(const std::vector<Room>& rooms,
             const std::vector<Guest>& guests,
             const std::vector<Reservation>& reservations);