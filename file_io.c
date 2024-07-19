#include <stdio.h>
#include <stdlib.h>
#include "hotel.h"

void loadUsers() {
    FILE *file = fopen(USER_FILE, "r");
    if (file == NULL) {
        printf("No user data found.\n");
        return;
    }
    
    char line[MAX_NAME_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        printf("Loaded user: %s", line);
    }
    
    fclose(file);
}

void exportServiceRequestsToCSV() {
    FILE *file = fopen("service_requests.csv", "w");
    if (file == NULL) {
        printf("Error opening CSV file.\n");
        return;
    }
    
    fprintf(file, "Room Number,Request Description,Completed\n");
    
    for (int i = 0; i < MAX_ROOMS; i++) {
        Room room = rooms[i];
        for (int j = 0; j < room.serviceRequestCount; j++) {
            ServiceRequest request = room.serviceRequests[j];
            fprintf(file, "%d,%s,%d\n", room.roomNumber, request.description, request.isCompleted);
        }
    }
    
    fclose(file);
    printf("Service requests exported to CSV.\n");
}
