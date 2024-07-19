#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

#define ADMIN_PASSWORD "admin123"
#define USER_FILE "users.dat"

void manageUsers() {
    // Manage users logic
}

int authenticateUser() {
    char password[MAX_NAME_LENGTH];
    
    printf("Enter password: ");
    fgets(password, MAX_NAME_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';
    
    return strcmp(password, ADMIN_PASSWORD) == 0;
}
