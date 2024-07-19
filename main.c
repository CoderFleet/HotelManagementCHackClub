#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOMS 100
#define MAX_NAME_LENGTH 50
#define DATA_FILE "rooms.dat"

typedef struct {
    int roomNumber;
    int isOccupied;
    char guestName[MAX_NAME_LENGTH];
} Room;

Room rooms[MAX_ROOMS];

void initializeRooms();
void loadRooms();
void saveRooms();
void displayMenu();
void checkIn();
void checkOut();
void viewRooms();
void searchRoom();
void waitForUserInput();

void initializeRooms() {
    for (int i = 0; i < MAX_ROOMS; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].isOccupied = 0;
        strcpy(rooms[i].guestName, "");
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
    printf("1. Check In\n");
    printf("2. Check Out\n");
    printf("3. View Rooms\n");
    printf("4. Search Room\n");
    printf("5. Save and Exit\n");
    printf("Enter your choice: ");
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

void waitForUserInput() {
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}

int main() {
    int choice;

    initializeRooms();
    loadRooms();

    while (1) {
        displayMenu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                checkIn();
                break;
            case 2:
                checkOut();
                break;
            case 3:
                viewRooms();
                break;
            case 4:
                searchRoom();
                break;
            case 5:
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
