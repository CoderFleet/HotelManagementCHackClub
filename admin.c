#include <stdio.h>
#include <stdlib.h>
#include "hotel.h"
#include "user.h"
#include "file_io.h"

void generateReport() {
    FILE *file = fopen("report.txt", "w");
    if (file == NULL) {
        printf("Error opening report file.\n");
        return;
    }
    
    fprintf(file, "Hotel Report\n\n");
    fprintf(file, "Room Number\tOccupied\tGuest Name\tPrice\tType\n");
    
    for (int i = 0; i < MAX_ROOMS; i++) {
        Room room = rooms[i];
        fprintf(file, "%d\t%s\t%s\t%.2f\t%s\n",
                room.roomNumber,
                room.isOccupied ? "Yes" : "No",
                room.guestName,
                room.roomPrice,
                room.roomType);
    }
    
    fclose(file);
    printf("Report generated.\n");
}

void waitForUserInput() {
    printf("Press Enter to continue...");
    getchar();
}
