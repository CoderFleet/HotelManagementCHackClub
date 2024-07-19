#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

#define ADMIN_PASSWORD "admin123"
#define USER_FILE "users.dat"

void manageUsers() {
    FILE *file = fopen(USER_FILE, "r+");
    if (file == NULL) {
        printf("Unable to open user data file.\n");
        return;
    }
    
    char command[100];
    while (1) {
        printf("1. Add User\n2. Remove User\n3. List Users\n4. Exit\nEnter your choice: ");
        fgets(command, sizeof(command), stdin);
        int choice = atoi(command);
        
        switch (choice) {
            case 1: {
                char username[100];
                printf("Enter username to add: ");
                fgets(username, sizeof(username), stdin);
                username[strcspn(username, "\n")] = '\0';
                
                fprintf(file, "%s\n", username);
                printf("User added.\n");
                break;
            }
            case 2: {
                printf("Removing users functionality is not yet implemented.\n");
                break;
            }
            case 3: {
                char line[100];
                printf("List of users:\n");
                while (fgets(line, sizeof(line), file)) {
                    printf("%s", line);
                }
                fseek(file, 0, SEEK_SET);
                break;
            }
            case 4:
                fclose(file);
                return;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }
}

int authenticateUser() {
    char password[MAX_NAME_LENGTH];
    
    printf("Enter password: ");
    fgets(password, MAX_NAME_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';
    
    return strcmp(password, ADMIN_PASSWORD) == 0;
}
