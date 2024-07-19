#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOMS 100
#define MAX_NAME_LENGTH 50
#define DATA_FILE "rooms.dat"
#define MAX_HISTORY 10
#define MAX_SERVICE_REQUESTS 5

typedef struct {
    char description[MAX_NAME_LENGTH];
    int isCompleted;
} ServiceRequest;

typedef struct {
    int roomNumber;
    int isOccupied;
    char guestName[MAX_NAME_LENGTH];
    char reservationHistory[MAX_HISTORY][MAX_NAME_LENGTH];
    int historyCount;
    ServiceRequest serviceRequests[MAX_SERVICE_REQUESTS];
    int serviceRequestCount;
} Room;

Room rooms[MAX_ROOMS];
char adminUsername[] = "admin";
char adminPassword[] = "password";

void initializeRooms();
void loadRooms();
void saveRooms();
void displayMenu();
void checkIn();
void checkOut();
void viewRooms();
void searchRoom();
void viewReservationHistory(int roomNumber);
void clearReservationHistory(int roomNumber);
void waitForUserInput();
int authenticateAdmin();
void displayAdminMenu();
void addRoomService(int roomNumber);
void viewRoomServiceRequests(int roomNumber);
void markServiceRequestComplete(int roomNumber, int requestIndex);

void initializeRooms() {
    for (int i = 0; i < MAX_ROOMS; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].isOccupied = 0;
        strcpy(rooms[i].guestName, "");
        rooms[i].historyCount = 0;
        rooms[i].serviceRequestCount = 0;
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

void displayMenu() {
    printf("Hotel Management System\n");
    printf("1. Admin Login\n");
    printf("2. View Rooms\n");
    printf("3. Search Room\n");
    printf("4. Save and Exit\n");
    printf("Enter your choice: ");
}

void displayAdminMenu() {
    printf("Admin Menu\n");
    printf("1. Check In\n");
    printf("2. Check Out\n");
    printf("3. View Reservation History\n");
    printf("4. Clear Reservation History\n");
    printf("5. Add Room Service Request\n");
    printf("6. View Room Service Requests\n");
    printf("7. Mark Room Service Request Complete\n");
    printf("8. Logout\n");
    printf("Enter your choice: ");
}

int authenticateAdmin() {
    char username[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];

    printf("Enter admin username: ");
    fgets(username, MAX_NAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter admin password: ");
    fgets(password, MAX_NAME_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(username, adminUsername) == 0 && strcmp(password, adminPassword) == 0) {
        return 1;
    } else {
        printf("Invalid credentials.\n");
        return 0;
    }
}

void checkIn() {
    int roomNumber;
    char guestName[MAX_NAME_LENGTH];
    printf("Enter room number to check in: ");
    scanf("%d", &roomNumber);
    getchar();
    if (roomNumber > 0 && roomNumber <= MAX_ROOMS) {
        if (rooms[roomNumber - 1].isOccupied) {
            printf("Room %d is already occupied.\n", roomNumber);
        } else {
            printf("Enter guest name: ");
            fgets(guestName, MAX_NAME_LENGTH, stdin);
            guestName[strcspn(guestName, "\n")] = '\0';
            rooms[roomNumber - 1].isOccupied = 1;
            strcpy(rooms[roomNumber - 1].guestName, guestName);
            if (rooms[roomNumber - 1].historyCount < MAX_HISTORY) {
                strcpy(rooms[roomNumber - 1].reservationHistory[rooms[roomNumber - 1].historyCount], guestName);
                rooms[roomNumber - 1].historyCount++;
            }
            printf("Checked in to room %d for %s.\n", roomNumber, guestName);
        }
    } else {
        printf("Invalid room number.\n");
    }
    waitForUserInput();
}

void checkOut() {
    int roomNumber;
    printf("Enter room number to check out: ");
    scanf("%d", &roomNumber);
    getchar();
    if (roomNumber > 0 && roomNumber <= MAX_ROOMS) {
        if (rooms[roomNumber - 1].isOccupied) {
            rooms[roomNumber - 1].isOccupied = 0;
            strcpy(rooms[roomNumber - 1].guestName, "");
            printf("Checked out from room %d.\n", roomNumber);
        } else {
            printf("Room %d is not occupied.\n", roomNumber);
        }
    } else {
        printf("Invalid room number.\n");
    }
    waitForUserInput();
}

void viewRooms() {
    printf("Room Status:\n");
    for (int i = 0; i < MAX_ROOMS; i++) {
        printf("Room %d: %s", rooms[i].roomNumber, rooms[i].isOccupied ? "Occupied" : "Available");
        if (rooms[i].isOccupied) {
            printf(" - Guest: %s", rooms[i].guestName);
        }
        printf("\n");
    }
    waitForUserInput();
}

void searchRoom() {
    int roomNumber;
    printf("Enter room number to search: ");
    scanf("%d", &roomNumber);
    getchar();
    if (roomNumber > 0 && roomNumber <= MAX_ROOMS) {
        if (rooms[roomNumber - 1].isOccupied) {
            printf("Room %d is occupied by %s.\n", roomNumber, rooms[roomNumber - 1].guestName);
        } else {
            printf("Room %d is available.\n", roomNumber);
        }
    } else {
        printf("Invalid room number.\n");
    }
    waitForUserInput();
}

void viewReservationHistory(int roomNumber) {
    if (roomNumber > 0 && roomNumber <= MAX_ROOMS) {
        printf("Reservation History for Room %d:\n", roomNumber);
        for (int i = 0; i < rooms[roomNumber - 1].historyCount; i++) {
            printf("%d. %s\n", i + 1, rooms[roomNumber - 1].reservationHistory[i]);
        }
    } else {
        printf("Invalid room number.\n");
    }
    waitForUserInput();
}

void clearReservationHistory(int roomNumber) {
    if (roomNumber > 0 && roomNumber <= MAX_ROOMS) {
        rooms[roomNumber - 1].historyCount = 0;
        printf("Reservation history for room %d cleared.\n", roomNumber);
    } else {
        printf("Invalid room number.\n");
    }
    waitForUserInput();
}

void addRoomService(int roomNumber) {
    if (roomNumber > 0 && roomNumber <= MAX_ROOMS) {
        if (rooms[roomNumber - 1].serviceRequestCount < MAX_SERVICE_REQUESTS) {
            printf("Enter service request description: ");
            char description[MAX_NAME_LENGTH];
            fgets(description, MAX_NAME_LENGTH, stdin);
            description[strcspn(description, "\n")] = '\0';
            ServiceRequest newRequest;
            strcpy(newRequest.description, description);
            newRequest.isCompleted = 0;
            rooms[roomNumber - 1].serviceRequests[rooms[roomNumber - 1].serviceRequestCount] = newRequest;
            rooms[roomNumber - 1].serviceRequestCount++;
            printf("Service request added for room %d.\n", roomNumber);
        } else {
            printf("Room %d has reached the maximum number of service requests.\n", roomNumber);
        }
    } else {
        printf("Invalid room number.\n");
    }
    waitForUserInput();
}

void viewRoomServiceRequests(int roomNumber) {
    if (roomNumber > 0 && roomNumber <= MAX_ROOMS) {
        printf("Service Requests for Room %d:\n", roomNumber);
        for (int i = 0; i < rooms[roomNumber - 1].serviceRequestCount; i++) {
            printf("%d. %s - %s\n", i + 1, rooms[roomNumber - 1].serviceRequests[i].description,
                   rooms[roomNumber - 1].serviceRequests[i].isCompleted ? "Completed" : "Pending");
        }
    } else {
        printf("Invalid room number.\n");
    }
    waitForUserInput();
}

void markServiceRequestComplete(int roomNumber, int requestIndex) {
    if (roomNumber > 0 && roomNumber <= MAX_ROOMS) {
        if (requestIndex > 0 && requestIndex <= rooms[roomNumber - 1].serviceRequestCount) {
            rooms[roomNumber - 1].serviceRequests[requestIndex - 1].isCompleted = 1;
            printf("Service request %d for room %d marked as completed.\n", requestIndex, roomNumber);
        } else {
            printf("Invalid service request index.\n");
        }
    } else {
        printf("Invalid room number.\n");
    }
    waitForUserInput();
}

void waitForUserInput() {
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}

int main() {
    int choice;
    int roomNumber;
    int requestIndex;

    initializeRooms();
    loadRooms();

    while (1) {
        displayMenu();
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                if (authenticateAdmin()) {
                    while (1) {
                        displayAdminMenu();
                        scanf("%d", &choice);
                        getchar();
                        if (choice == 8) break;
                        switch (choice) {
                            case 1:
                                checkIn();
                                break;
                            case 2:
                                checkOut();
                                break;
                            case 3:
                                printf("Enter room number to view reservation history: ");
                                scanf("%d", &roomNumber);
                                getchar();
                                viewReservationHistory(roomNumber);
                                break;
                            case 4:
                                printf("Enter room number to clear reservation history: ");
                                scanf("%d", &roomNumber);
                                getchar();
                                clearReservationHistory(roomNumber);
                                break;
                            case 5:
                                printf("Enter room number to add service request: ");
                                scanf("%d", &roomNumber);
                                getchar();
                                addRoomService(roomNumber);
                                break;
                            case 6:
                                printf("Enter room number to view service requests: ");
                                scanf("%d", &roomNumber);
                                getchar();
                                viewRoomServiceRequests(roomNumber);
                                break;
                            case 7:
                                printf("Enter room number to mark service request complete: ");
                                scanf("%d", &roomNumber);
                                getchar();
                                printf("Enter service request index to mark complete: ");
                                scanf("%d", &requestIndex);
                                getchar();
                                markServiceRequestComplete(roomNumber, requestIndex);
                                break;
                            default:
                                printf("Invalid choice, please try again.\n");
                                waitForUserInput();
                        }
                    }
                }
                break;
            case 2:
                viewRooms();
                break;
            case 3:
                searchRoom();
                break;
            case 4:
                saveRooms();
                printf("Data saved. Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
                waitForUserInput();
        }
    }

    return 0;
}
