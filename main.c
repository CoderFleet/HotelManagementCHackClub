#include <stdio.h>
#include <stdlib.h>

#define MAX_ROOMS 100

typedef struct {
    int roomNumber;
    int isOccupied;
} Room;

Room rooms[MAX_ROOMS];

void pause() {
    printf("Press Enter to continue...");
    while (getchar() != '\n');
    getchar(); // Consume the newline character
}

void initializeRooms() {
    for (int i = 0; i < MAX_ROOMS; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].isOccupied = 0;
    }
}

void displayMenu() {
    printf("Hotel Management System\n");
    printf("1. Check In\n");
    printf("2. Check Out\n");
    printf("3. View Rooms\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

void checkIn() {
    int roomNumber;
    printf("Enter room number to check in: ");
    scanf("%d", &roomNumber);

    if (roomNumber > 0 && roomNumber <= MAX_ROOMS) {
        if (rooms[roomNumber - 1].isOccupied) {
            printf("Room %d is already occupied.\n", roomNumber);
        } else {
            rooms[roomNumber - 1].isOccupied = 1;
            printf("Checked in to room %d.\n", roomNumber);
        }
    } else {
        printf("Invalid room number.\n");
    }
    pause();
}

void checkOut() {
    int roomNumber;
    printf("Enter room number to check out: ");
    scanf("%d", &roomNumber);

    if (roomNumber > 0 && roomNumber <= MAX_ROOMS) {
        if (rooms[roomNumber - 1].isOccupied) {
            rooms[roomNumber - 1].isOccupied = 0;
            printf("Checked out from room %d.\n", roomNumber);
        } else {
            printf("Room %d is not occupied.\n", roomNumber);
        }
    } else {
        printf("Invalid room number.\n");
    }
    pause();
}

void viewRooms() {
    printf("Room Status:\n");
    for (int i = 0; i < MAX_ROOMS; i++) {
        printf("Room %d: %s\n", rooms[i].roomNumber, rooms[i].isOccupied ? "Occupied" : "Available");
    }
    pause();
}

int main() {
    int choice;

    initializeRooms();

    while (1) {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Consume newline character left by scanf

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
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
                pause();
        }
    }

    return 0;
}
