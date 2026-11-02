#pragma once

#include <string>
#include <vector>

// Room type and structure
enum class RoomType {Single, Double, Suite};
enum class RoomStatus {Available, Occupied, Reserved};

struct Room {
    int number{};
    RoomType type{RoomType::Single};
    int pricePerNightCents{};
    int capacity{};
    int floor{};
    RoomStatus status{RoomStatus::Available};
};

// string helpers
std::string roomTypeToString(RoomType type);
std::string roomStatusToString(RoomStatus status);

// room operations
void listRooms(const std::vector<Room>& rooms);
bool roomNumberExists(const std::vector<Room>& rooms, int number);
bool addRoom(std::vector<Room>& rooms, const Room& room);
void addRoomMenu(std::vector<Room>& rooms);
void editRoom(std::vector<Room>& rooms);
void deleteRoom(std::vector<Room>& rooms);
void filterRoomsByStatus(const std::vector<Room>& rooms);

// menu
void roomManagementMenu(std::vector<Room>& rooms);