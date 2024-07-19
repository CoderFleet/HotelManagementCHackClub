#ifndef HOTEL_H
#define HOTEL_H

#define MAX_ROOMS 100
#define MAX_NAME_LENGTH 100
#define MAX_SERVICE_REQUESTS 10
#define DATA_FILE "rooms.dat"

typedef struct {
    int roomNumber;
    int isOccupied;
    char guestName[MAX_NAME_LENGTH];
    char reservationHistory[MAX_NAME_LENGTH][MAX_NAME_LENGTH];
    int historyCount;
    struct {
        char description[MAX_NAME_LENGTH];
        int isCompleted;
    } serviceRequests[MAX_SERVICE_REQUESTS];
    int serviceRequestCount;
    double roomPrice;
    char roomType[MAX_NAME_LENGTH];
} Room;

void initializeRooms();
void loadRooms();
void saveRooms();
void addRoomService(int roomNumber);
void viewRoomServiceRequests(int roomNumber);
void markServiceRequestComplete(int roomNumber, int requestIndex);
void viewReservationHistory(int roomNumber);
void clearReservationHistory(int roomNumber);
void checkIn();
void checkOut();
void viewRooms();
void searchRoom();

#endif