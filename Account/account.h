#pragma once

#include <string>
#include <vector>

#include "../Guest Management/guest.h"

// A login account. Each account belongs to one guest profile (guestId).
struct Account {
    std::string username;
    std::string password;
    int guestId{};
};

bool usernameExists(const std::vector<Account>& accounts, const std::string& username);

// Asks for username, password and guest profile details, then creates both
// the Account and its Guest. Returns true if the account was created.
bool registerAccount(std::vector<Account>& accounts, std::vector<Guest>& guests);

// Asks for username and password (up to 3 attempts).
// Returns the account's guestId on success, or -1 on failure.
int signIn(const std::vector<Account>& accounts);