# Hotel Reservation System

A terminal-based hotel reservation system written in C++. There is no GUI: everything runs through a text menu in the console. Guests can book rooms by themselves, and admins manage the whole hotel.

## Roles

The system has two roles.

- Admin has full access to the system.
- Guest has limited access. Including: search rooms, make reservation (view, modify, cancel reservation)


### Account rules

- Guests can only self-register as the Guest role. The signup screen never lets the user choose a role.
- A default admin account is created on first run if no users file exists. The admin is asked to change the password immediately.
- Only an existing admin can create new admin accounts.
- Passwords are stored as hashes, never as plain text.
- Permissions are enforced in the business logic, not just by hiding menu options.

## Features

### Core

**Room management (Admin)**
- Add, edit, and remove rooms (room number, type, price per night, capacity, floor)
- Room types: Single, Double, Suite
- Room status: Available, Occupied, Reserved
- View all rooms and filter by type or status

**Guest management**
- Guest self-registration with username and password
- Admin can create guest profiles for walk-ins (no login needed)
- Search guests by name, phone, or ID (Admin)
- Guest profile: name, phone, email, ID/passport number

**Reservations**
- Search available rooms by date range, room type, and number of guests
- Create a reservation with a unique booking ID
- Double-booking prevention through an overlap check
- Modify or cancel a reservation
- Status flow: `Pending -> Confirmed -> Checked-in -> Checked-out`, plus `Cancelled` and `No-show`

**Check-in and check-out (Admin)**
- Check in a guest against an existing reservation
- Check out and automatically calculate the total bill (nights x rate)
- Room status updates automatically


## Data Storage

There is no database server. All data is saved to JSON files in a `data/` folder and loaded when the program starts.

| File | Contents |
|---|---|
| `data/users.json` | Accounts (username, password hash, role) |
| `data/guests.json` | Guest profiles |
| `data/rooms.json` | Rooms, types, prices, status |
| `data/reservations.json` | All bookings |

Example `rooms.json`:

```json
[
  { "number": 101, "type": "Single", "pricePerNight": 50, "capacity": 1, "floor": 1, "status": "Available" },
  { "number": 201, "type": "Double", "pricePerNight": 90, "capacity": 2, "floor": 2, "status": "Available" },
  { "number": 301, "type": "Suite",  "pricePerNight": 150, "capacity": 4, "floor": 3, "status": "Available" }
]
```

Notes:
- JSON is read and written with the [nlohmann/json](https://github.com/nlohmann/json) library (a single header file, `json.hpp`).
- Files are created automatically on first run if they do not exist.
- Data is saved after every change (new booking, cancellation, check-in, and so on), so nothing is lost if the program closes.
- Dates are stored as strings in `YYYY-MM-DD` format.
- Save to a temporary file first and then rename it, so a crash in the middle of a write cannot corrupt the data file.

Default admin account on first run: `admin` / `admin123` (change it immediately).