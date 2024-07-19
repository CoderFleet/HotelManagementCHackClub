#include <stdio.h>
#include <stdlib.h>
#include "hotel.h"
#include "user.h"
#include "admin.h"
#include "file_io.h"

void displayMenu();
void displayAdminMenu();

int main() {
    initializeRooms();
    loadRooms();
    loadUsers();
    
    int choice;
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
                displayAdminMenu();
                break;
            case 6:
                saveRooms();
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }
}

void displayMenu() {
    printf("1. Check In\n2. Check Out\n3. View Rooms\n4. Search Room\n5. Admin Menu\n6. Exit\n");
}

void displayAdminMenu() {
    int choice;
    while (1) {
        printf("1. Generate Report\n2. Export Service Requests\n3. Manage Users\n4. Back\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                generateReport();
                break;
            case 2:
                exportServiceRequestsToCSV();
                break;
            case 3:
                // Implement manageUsers()
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }
}
