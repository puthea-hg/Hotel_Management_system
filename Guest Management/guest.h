#pragma once

#include <string>
#include <vector>

// structure for guest profile
struct Guest {
    int id{};
    std::string name;
    std::string phone;
    std::string email;
    std::string passportId;
};

void addGuest(std::vector<Guest>& guests);
void listGuests(const std::vector<Guest>& guests);
void editGuest(std::vector<Guest>& guests);
void deleteGuest(std::vector<Guest>& guests);
void searchGuest(const std::vector<Guest>& guests);

// Returns the guest with this ID, or nullptr if there is none.
const Guest* findGuestById(const std::vector<Guest>& guests, int id);

// menu
void guestManagementMenu(std::vector<Guest>& guests);