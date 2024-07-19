#include <stdio.h>
#include <string.h>
#include "hotel.h"
#include "admin.h"

Room rooms[MAX_ROOMS];

void initializeRooms() {
    for (int i = 0; i < MAX_ROOMS; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].isOccupied = 0;
        strcpy(rooms[i].guestName, "");
        rooms[i].historyCount = 0;
        rooms[i].serviceRequestCount = 0;
        rooms[i].roomPrice = 0.0;
        strcpy(rooms[i].roomType, "Standard");
    }
}

void addRoomService(int roomNumber) {
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
    
    if (rooms[roomNumber - 1].serviceRequestCount >= MAX_SERVICE_REQUESTS) {
        printf("Service request limit reached.\n");
        waitForUserInput();
        return;
    }
    
    char description[MAX_NAME_LENGTH];
    printf("Enter service description: ");
    fgets(description, sizeof(description), stdin);
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
    printf("Room Number: %d\n", room.roomNumber);
    printf("Service Requests:\n");
    for (int i = 0; i < room.serviceRequestCount; i++) {
        ServiceRequest request = room.serviceRequests[i];
        printf("%d. %s - %s\n", i + 1, request.description, request.isCompleted ? "Completed" : "Pending");
    }
    waitForUserInput();
}

void markServiceRequestComplete(int roomNumber, int requestIndex) {
    if (roomNumber < 1 || roomNumber > MAX_ROOMS) {
        printf("Invalid room number.\n");
        waitForUserInput();
        return;
    }
    
    if (requestIndex < 0 || requestIndex >= rooms[roomNumber - 1].serviceRequestCount) {
        printf("Invalid service request index.\n");
        waitForUserInput();
        return;
    }
    
    rooms[roomNumber - 1].serviceRequests[requestIndex].isCompleted = 1;
    printf("Service request marked as complete.\n");
    waitForUserInput();
}

void viewReservationHistory(int roomNumber) {
    if (roomNumber < 1 || roomNumber > MAX_ROOMS) {
        printf("Invalid room number.\n");
        waitForUserInput();
        return;
    }
    
    Room room = rooms[roomNumber - 1];
    printf("Room Number: %d\n", room.roomNumber);
    printf("Reservation History:\n");
    for (int i = 0; i < room.historyCount; i++) {
        printf("%d. %s\n", i + 1, room.reservationHistory[i]);
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
