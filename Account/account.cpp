#include "account.h"

#include <iostream>

using namespace std;

namespace {

// text must be long enough and must not contain the file delimiter '|'
bool isValidText(const string& text, size_t minLength){
    return text.size() >= minLength && text.find('|') == string::npos;
}

} // namespace

bool usernameExists(const vector<Account>& accounts, const string& username){
    for(const Account& account : accounts){
        if(account.username == username){
            return true;
        }
    }
    return false;
}

bool registerAccount(vector<Account>& accounts, vector<Guest>& guests){
    Account account;

    cout << "Choose a username (at least 3 characters, no '|'): ";
    cin >> account.username;
    if(!cin){
        return false;
    }
    if(!isValidText(account.username, 3)){
        cout << "Invalid username.\n";
        return false;
    }
    if(usernameExists(accounts, account.username)){
        cout << "That username is already taken.\n";
        return false;
    }

    string retype;
    while(true){
        cout << "Please enter your password (at least 4 characters, no '|'): ";
        cin >> account.password;
        if(!cin){
            return false;
        }
        if(!isValidText(account.password, 4)){
            cout << "Invalid password.\n";
            continue;
        }

        cout << "Please retype your password: ";
        cin >> retype;
        if(!cin){
            return false;
        }
        if(account.password == retype){
            break;
        }
        cout << "Passwords do not match. Please try again.\n";
    }

    cout << "\nNow enter your guest profile details.\n";
    addGuest(guests);
    account.guestId = guests.back().id;

    accounts.push_back(account);
    cout << "Account created successfully!\n";
    return true;
}

int signIn(const vector<Account>& accounts){
    const int MAX_ATTEMPTS = 3;

    for(int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++){
        string username;
        string password;

        cout << "Please Enter your username: ";
        cin >> username;
        cout << "Please Enter your password: ";
        cin >> password;
        if(!cin){
            return -1;
        }

        for(const Account& account : accounts){
            if(account.username == username && account.password == password){
                return account.guestId;
            }
        }

        cout << "Incorrect username or password. Attempts left: "
             << MAX_ATTEMPTS - attempt << "\n";
    }

    return -1;
}