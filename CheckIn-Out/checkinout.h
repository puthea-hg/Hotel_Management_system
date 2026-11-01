#pragma once

#include <vector>

#include "../Room Management/room.h"
#include "../Reservation System/reservation.h"

double calculateBill(int roomPricePerNightCents, int nights);

void checkIn(std::vector<Reservation>& reservations, std::vector<Room>& rooms);
void checkOut(std::vector<Reservation>& reservations, std::vector<Room>& rooms);

// menu
void checkInOutMenu(std::vector<Reservation>& reservations, std::vector<Room>& rooms);