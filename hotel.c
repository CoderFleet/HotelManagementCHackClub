#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel.h"

Room rooms[MAX_ROOMS];

void initializeRooms() {
    for (int i = 0; i < MAX_ROOMS; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].isOccupied = 0;
        strcpy(rooms[i].guestName, "");
        rooms[i].historyCount = 0;
        rooms[i].serviceRequestCount = 0;
        rooms[i].roomPrice = 100.0;
        strcpy(rooms[i].roomType, "Standard");
    }
}

void loadRooms() {
    FILE *file = fopen(DATA_FILE, "rb");
    if (file == NULL) {
        printf("No existing room data found, starting fresh.\n");
        return;
    }
    fread(rooms, sizeof(Room), MAX_ROOMS, file);
    fclose(file);
}

void saveRooms() {
    FILE *file = fopen(DATA_FILE, "wb");
    if (file == NULL) {
        printf("Error saving room data.\n");
        return;
    }
    fwrite(rooms, sizeof(Room), MAX_ROOMS, file);
    fclose(file);
}

void addRoomService(int roomNumber) {
    char description[MAX_NAME_LENGTH];
    
    if (roomNumber < 1 || roomNumber > MAX_ROOMS) {
        printf("Invalid room number.\n");
        waitForUserInput();
        return;
    }
    
    if (rooms[roomNumber - 1].serviceRequestCount >= MAX_SERVICE_REQUESTS) {
        printf("Max service requests reached for this room.\n");
        waitForUserInput();
        return;
    }
    
    printf("Enter service request description: ");
    fgets(description, MAX_NAME_LENGTH, stdin);
    description[strcspn(description, "\n")] = '\0';
    
    ServiceRequest *request = &rooms[roomNumber - 1].serviceRequests[rooms[roomNumber - 1].serviceRequestCount++];
    strcpy(request->description, description);
    request->isCompleted = 0;
    
    printf("Service request added.\n");
    waitForUserInput();
}

void viewRoomServiceRequests(int roomNumber) {
    if (roomNumber < 1 || roomNumber > MAX_ROOMS) {
        printf("Invalid room number.\n");
        waitForUserInput();
        return;
    }
    
    Room room = rooms[roomNumber - 1];
    printf("Service Requests for Room %d:\n", room.roomNumber);
    for (int i = 0; i < room.serviceRequestCount; i++) {
        ServiceRequest request = room.serviceRequests[i];
        printf("Request %d: %s (Completed: %s)\n",
               i + 1,
               request.description,
               request.isCompleted ? "Yes" : "No");
    }
    waitForUserInput();
}

void markServiceRequestComplete(int roomNumber, int requestIndex) {
    if (roomNumber < 1 || roomNumber > MAX_ROOMS) {
        printf("Invalid room number.\n");
        waitForUserInput();
        return;
    }
    
    if (requestIndex < 1 || requestIndex > rooms[roomNumber - 1].serviceRequestCount) {
        printf("Invalid request index.\n");
        waitForUserInput();
        return;
    }
    
    rooms[roomNumber - 1].serviceRequests[requestIndex - 1].isCompleted = 1;
    printf("Service request marked complete.\n");
    waitForUserInput();
}

void viewReservationHistory(int roomNumber) {
    if (roomNumber < 1 || roomNumber > MAX_ROOMS) {
        printf("Invalid room number.\n");
        waitForUserInput();
        return;
    }
    
    Room room = rooms[roomNumber - 1];
    printf("Reservation History for Room %d:\n", room.roomNumber);
    for (int i = 0; i < room.historyCount; i++) {
        printf("%d: %s\n", i + 1, room.reservationHistory[i]);
    }
    waitForUserInput();
}

void clearReservationHistory(int roomNumber) {
    if (roomNumber < 1 || roomNumber > MAX_ROOMS) {
        printf("Invalid room number.\n");
        waitForUserInput();
        return;
    }
    
    rooms[roomNumber - 1].historyCount = 0;
    printf("Reservation history cleared.\n");
    waitForUserInput();
}

void checkIn() {
    int roomNumber;
    char guestName[MAX_NAME_LENGTH];
    
    printf("Enter room number: ");
    scanf("%d", &roomNumber);
    getchar();
    
    if (roomNumber < 1 || roomNumber > MAX_ROOMS) {
        printf("Invalid room number.\n");
        waitForUserInput();
        return;
    }
    
    if (rooms[roomNumber - 1].isOccupied) {
        printf("Room already occupied.\n");
        waitForUserInput();
        return;
    }
    
    printf("Enter guest name: ");
    fgets(guestName, MAX_NAME_LENGTH, stdin);
    guestName[strcspn(guestName, "\n")] = '\0';
    
    rooms[roomNumber - 1].isOccupied = 1;
    strcpy(rooms[roomNumber - 1].guestName, guestName);
    printf("Checked in successfully.\n");
    waitForUserInput();
}

void checkOut() {
    int roomNumber;
    
    printf("Enter room number: ");
    scanf("%d", &roomNumber);
    getchar();
    
    if (roomNumber < 1 || roomNumber > MAX_ROOMS) {
        printf("Invalid room number.\n");
        waitForUserInput();
        return;
    }
    
    if (!rooms[roomNumber - 1].isOccupied) {
        printf("Room is not occupied.\n");
        waitForUserInput();
        return;
    }
    
    rooms[roomNumber - 1].isOccupied = 0;
    strcpy(rooms[roomNumber - 1].guestName, "");
    printf("Checked out successfully.\n");
    waitForUserInput();
}

void viewRooms() {
    printf("Room Number\tOccupied\tGuest Name\tPrice\tType\n");
    for (int i = 0; i < MAX_ROOMS; i++) {
        printf("%d\t%s\t%s\t%.2f\t%s\n",
               rooms[i].roomNumber,
               rooms[i].isOccupied ? "Yes" : "No",
               rooms[i].guestName,
               rooms[i].roomPrice,
               rooms[i].roomType);
    }
    waitForUserInput();
}

void searchRoom() {
    int roomNumber;
    
    printf("Enter room number to search: ");
    scanf("%d", &roomNumber);
    getchar();
    
    if (roomNumber < 1 || roomNumber > MAX_ROOMS) {
        printf("Invalid room number.\n");
        waitForUserInput();
        return;
    }
    
    Room room = rooms[roomNumber - 1];
    printf("Room Number: %d\n", room.roomNumber);
    printf("Occupied: %s\n", room.isOccupied ? "Yes" : "No");
    printf("Guest Name: %s\n", room.guestName);
    printf("Price: %.2f\n", room.roomPrice);
    printf("Type: %s\n", room.roomType);
    waitForUserInput();
}
