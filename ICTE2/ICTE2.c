#include <stdio.h>
#include <stdlib.h>

#define MAX_USERS 5  // Define maximum number of users

typedef struct {
    int id;
    char name[100];
    int age;
} UserInfo;

// Updated function prototypes
void getUserInfo(UserInfo users[], int count);
void saveUserInfo(const UserInfo users[], int count);
void displayUserInfo(const UserInfo* user);
int searchUserById(const UserInfo users[], int count, int id);

int main() {
    UserInfo users[MAX_USERS];  // Declare an array of UserInfo

    // Get information for multiple users
    getUserInfo(users, MAX_USERS);

    // Save information to a file (optional extension)
    saveUserInfo(users, MAX_USERS);

    int searchId;
    printf("Enter ID to search: ");
    scanf("%d", &searchId);

    int index = searchUserById(users, MAX_USERS, searchId);

    if (index != -1) {
        // Display user information if found
        displayUserInfo(&users[index]);
    } else {
        printf("User not found.\n");
    }

    return 0;
}

// Update existing functions and add new functions
// Detailed comments should be provided explaining each part

// Function to get user information from input and store it in an array
void getUserInfo(UserInfo users[], int count) {
    for (int i = 0; i < count; i++) {
        printf("Enter user #%d information:\n", i + 1);
        printf("ID: ");
        scanf("%d", &users[i].id);  // Reading user ID from input
        printf("Name: ");
        scanf("%s", users[i].name);  // Reading user name from input
        printf("Age: ");
        scanf("%d", &users[i].age);  // Reading user age from input
    }
}

// Function to save user information into a file
void saveUserInfo(const UserInfo users[], int count) {
    FILE* fp = fopen("users.txt", "w");  // Opening a file for writing

    if (fp == NULL) {
        printf(
            "Error opening file.\n");  // Error handling if file opening fails
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        // Writing each user's information into the file
        fprintf(fp, "%d %s %d\n", users[i].id, users[i].name, users[i].age);
    }

    fclose(fp);  // Closing the file
}

// Function to display information of a single user
void displayUserInfo(const UserInfo* user) {
    printf("ID: %d\n", user->id);      // Printing user ID
    printf("Name: %s\n", user->name);  // Printing user name
    printf("Age: %d\n", user->age);    // Printing user age
}

// Function to search for a user by ID and return their index in the array
int searchUserById(const UserInfo users[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (users[i].id == id) {
            return i;  // Returning the index if a matching ID is found
        }
    }

    return -1;  // Returning -1 if no matching ID is found
}