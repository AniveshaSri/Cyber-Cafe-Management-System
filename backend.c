#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERS 50
#define USERNAME_LENGTH 100
#define PASSWORD_LENGTH 100

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    time_t session_start;
    time_t session_end;
    int is_logged_in;
} User;

User users[MAX_USERS];
int user_count = 0;

void register_user() {
    if (user_count >= MAX_USERS) {
        printf("User limit reached. Cannot register more users.\n");
        return;
    }

    User new_user;
    printf("Enter username: ");
    scanf("%s", new_user.username);
    printf("Enter password: ");
    scanf("%s", new_user.password);
    new_user.is_logged_in = 0;

    users[user_count++] = new_user;
    printf("User registered successfully!\n");
}

int login_user() {
    char username[USERNAME_LENGTH], password[PASSWORD_LENGTH];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            users[i].is_logged_in = 1;
            users[i].session_start = time(NULL);
            printf("Login successful! Welcome, %s!\n", username);
            return i; 
        }
    }
    printf("Invalid username or password.\n");
    return -1; 
}

void end_session(int user_index) {
    if (user_index < 0 || user_index >= user_count || !users[user_index].is_logged_in) {
        printf("Invalid user session.\n");
        return;
    }

    users[user_index].session_end = time(NULL);
    users[user_index].is_logged_in = 0;

    double seconds = difftime(users[user_index].session_end, users[user_index].session_start);
    double hours = seconds / 3600.0;
    double cost = hours * 5.0; 

    printf("Session ended. Total time: %.2f hours. Total cost: INR%.2f\n", hours, cost);
}

int main() {
    int choice, user_index;

    while (1) {
        printf("\nCyber Cafe Management System\n");
        printf("1. Register User\n");
        printf("2. Login User\n");
        printf("3. End Session\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                register_user();
                break;
            case 2:
                user_index = login_user();
                break;
            case 3:
                end_session(user_index);
                break;
            case 4:
                printf("Exiting the system. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
