# Hotel Reservation System

A console-based hotel reservation system written in C++. The program is
operated through text menus and stores its data in local text files.

## Current capabilities

### Admin login

The application currently provides one hard-coded admin login:

```text
Username: admin
Password: admin123
```

There are three login attempts.

### Room management

From the admin menu, you can:

- Add rooms with a number, type, capacity, floor, and nightly price
- View all rooms
- Edit a room's capacity and floor
- Delete a room
- Filter rooms by `Available`, `Occupied`, or `Reserved` status

The available room types are `Single`, `Double`, and `Suite`. Prices are
entered in dollars but stored as integer cents.

### Guest management

From the guest management menu, you can:

- Add a guest profile
- View all guests
- Edit a guest's name, phone number, email address, or passport ID by guest ID
- Delete a guest by guest ID
- Search for a guest by exact name

Each new guest receives an ID based on the highest existing ID. A guest
profile contains a name, phone number, email address, and passport ID.

### Reservations and stays

From the reservation menu, an administrator can:

- Book an available room for an existing guest
- View reservations
- Modify reservation dates
- Cancel a reservation
- Check a guest in
- Check a guest out and calculate the bill

Booking IDs are generated in the `BK1001`, `BK1002`, ... format. Reservation
statuses are:

- `Reserved`
- `Checked In`
- `Checked Out`
- `Cancelled`

When a reservation is created, its room becomes `Reserved`. Check-in changes
the room to `Occupied`; cancellation or check-out changes it back to
`Available`.

## Project layout

```text
.
├── main.cpp
├── input_utils.cpp
├── input_utils.h
├── Guest Management/
│   ├── guest.cpp
│   └── guest.h
├── Reservation System/
│   ├── reservation.cpp
│   └── reservation.h
├── Room Management/
│   ├── room.cpp
│   └── room.h
├── Storage/
│   ├── storage.cpp
│   └── storage.h
├── data/
│   ├── guests.txt
│   ├── reservations.txt
│   └── rooms.txt
```

## Building and running

From the project directory, compile all source files with a C++17-compatible
compiler:

```bash
g++ -std=c++17 \
  main.cpp input_utils.cpp \
  "Guest Management/guest.cpp" \
  "Reservation System/reservation.cpp" \
  "Room Management/room.cpp" \
  "Storage/storage.cpp" \
  -o hotel
```

Run the program with:

```bash
./hotel
```

On Windows, use the generated `hotel.exe` instead.

## Data persistence

The program loads the data files from the `data/` directory at startup and
saves all three files after each admin menu action:

| File | Contents |
|---|---|
| `data/rooms.txt` | Room number, type, price in cents, capacity, floor, and status |
| `data/guests.txt` | Guest ID, name, phone, email, and passport ID |
| `data/reservations.txt` | Booking ID, room number, guest name, dates, status, and guest ID |

Fields are separated by the pipe character (`|`), one record per line.
Because `|` is the delimiter, it is replaced with `/` when saving text
fields.

Example records:

```text
# data/rooms.txt
101|0|5000|2|2|0

# data/guests.txt
1|John|01234567|john@email.com|N012345

# data/reservations.txt
BK1001|201|John|2026-11-02|2026-11-04|1|1
```

The numeric enum values are:

| Value | Room type | Room status | Reservation status |
|---:|---|---|---|
| `0` | Single | Available | Reserved |
| `1` | Double | Occupied | Checked In |
| `2` | Suite | Reserved | Checked Out |
| `3` | — | — | Cancelled |

If `data/rooms.txt` does not exist on the first run, the program starts with
sample rooms 101 and 201. Missing guest and reservation files simply start
empty. The `data/` directory must exist before saving. Malformed records are
skipped while loading.

## Known limitations

The current implementation does not yet provide:

- Guest accounts or a guest self-service portal
- Password hashing or configurable users
- Date validation or reservation overlap checking
- Room filtering by type
- Guest search by phone or ID
- Automatic calculation of nights from the entered dates
- Atomic writes or a database backend