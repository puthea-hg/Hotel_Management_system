#pragma once

#include <string>
#include <vector>

#include "../Room Management/room.h"
#include "../Guest Management/guest.h"

// reservation status enum
enum class ReservationStatus {
    Reserved,
    CheckedIn,
    CheckedOut,
    Cancelled
};

// reservation struct
struct Reservation {
    std::string bookingId;
    int roomNumber{};
    std::string guestName;
    int guestId{};  // links to Guest::id (0 = not linked, e.g. older saved data)
    std::string checkedInDate;
    std::string checkOutDate;
    ReservationStatus status{ReservationStatus::Reserved};
};

std::string generateBookingId(const std::vector<Reservation>& reservations);
std::string reservationStatusToString(ReservationStatus status);

// Books a room for a specific guest (asks for room number and dates).
// Used by the admin booking and by the guest portal.
void bookRoomForGuest(std::vector<Reservation>& reservations,
                      std::vector<Room>& rooms,
                      const Guest& guest);

// Admin booking: asks for a Guest ID first, then books for that guest.
void bookRoom(std::vector<Reservation>& reservations,
              std::vector<Room>& rooms,
              const std::vector<Guest>& guests);
void listReservations(const std::vector<Reservation>& reservations);
void modifyReservation(std::vector<Reservation>& reservations);
void cancelReservation(std::vector<Reservation>& reservations, std::vector<Room>& rooms);

// check-in / check-out (part of the reservation flow)
double calculateBill(int roomPricePerNightCents, int nights);
void checkIn(std::vector<Reservation>& reservations, std::vector<Room>& rooms);
void checkOut(std::vector<Reservation>& reservations, std::vector<Room>& rooms);

// menu
void reservationMenu(std::vector<Reservation>& reservations,
                     std::vector<Room>& rooms,
                     const std::vector<Guest>& guests);