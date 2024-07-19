#include <stdio.h>
#include <stdlib.h>
#include "hotel.h"
#include "user.h"
#include "file_io.h"
#include "admin.h"

int main() {
    int choice;
    int isAdmin;

    initializeRooms();
    loadRooms();
    loadUsers();

    while (1) {
        displayMenu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                isAdmin = authenticateUser();
                if (isAdmin) {
                    while (1) {
                        displayAdminMenu();
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
                                {
                                    int roomNumber;
                                    printf("Enter room number to view reservation history: ");
                                    scanf("%d", &roomNumber);
                                    getchar();
                                    viewReservationHistory(roomNumber);
                                    break;
                                }
                            case 4:
                                {
                                    int roomNumber;
                                    printf("Enter room number to clear reservation history: ");
                                    scanf("%d", &roomNumber);
                                    getchar();
                                    clearReservationHistory(roomNumber);
                                    break;
                                }
                            case 5:
                                {
                                    int roomNumber;
                                    printf("Enter room number to add service request: ");
                                    scanf("%d", &roomNumber);
                                    getchar();
                                    addRoomService(roomNumber);
                                    break;
                                }
                            case 6:
                                {
                                    int roomNumber;
                                    printf("Enter room number to view service requests: ");
                                    scanf("%d", &roomNumber);
                                    getchar();
                                    viewRoomServiceRequests(roomNumber);
                                    break;
                                }
                            case 7:
                                {
                                    int roomNumber, requestIndex;
                                    printf("Enter room number to mark service request complete: ");
                                    scanf("%d", &roomNumber);
                                    getchar();
                                    printf("Enter service request index to mark complete: ");
                                    scanf("%d", &requestIndex);
                                    getchar();
                                    markServiceRequestComplete(roomNumber, requestIndex);
                                    break;
                                }
                            case 9:
                                manageUsers();
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
            case 5:
                generateReport();
                break;
            case 6:
                exportServiceRequestsToCSV();
                break;
            default:
                printf("Invalid choice, please try again.\n");
                waitForUserInput();
        }
    }

    return 0;
}
