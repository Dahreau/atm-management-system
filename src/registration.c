#include "header.h"
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define REGISTRATION_HEADER do { \
system("clear"); \
printf("\n\n\t\t======= Registration =======\n\n"); \
} while(0)

void Registration(struct User *u)
{
    //Sets the variables
    char username[50];
    char password[50];
    int idUser;

    //Checks if the username and password are valid and if the username is unique
    if (ChooseUsername(username)) {
        if (ChoosePassword(password)) {
            {
                //Generates a unique id for the user
                idUser = GenerateUniqueId();

                //Saves the user data in the users table
                strcpy(u->name, username);
                strcpy(u->password, password);
                u->id = idUser;

                FILE *fp = fopen("./data/users.txt", "a");

                if (fp == NULL) {
                    printf("Error opening file.\n");
                    return;
                }


                fprintf(fp, "\n%d %s %s", idUser, username, password);
                fclose(fp);

                printf("Registration successful! Your ID is %d.\n", idUser);
                success(*u);
            }
        }
    }
}

int ChooseUsername(char *username) {
    char confirmUsername[10];
    int isUniqueUsername = 1;
    int validConfirmUsername = 0;
    clearInputBuffer();

    do {
        REGISTRATION_HEADER;

        if (isUniqueUsername == 0) {
            printf("Username '%s' is already taken. Please choose a different username.\n", username);
        }
        
        printf("Choose a username : ");
        if (fgets(username, 50, stdin) == NULL) {
            printf("Error reading username.\n");
            continue;
        }
        username[strcspn(username, "\n")] = '\0'; // Remove newline character

        if (strlen(username) == 0) {
            printf("Username cannot be empty. Please enter a valid username.\n");
            validConfirmUsername = 0;
            continue;
        }

        // clearInputBuffer();

        // Check if username is valid
        if (ValidUsername(username)) {
            isUniqueUsername = 1;
            printf("Is '%s' correct? (Y/N) ", username); // Fix here
            if (fgets(confirmUsername, sizeof(confirmUsername), stdin) == NULL) {
                printf("Error reading confirmation.\n");
                continue;
            }
            confirmUsername[strcspn(confirmUsername, "\n")] = '\0'; // Remove newline character

            // Check if confirmation input is valid
            if (strlen(confirmUsername) != 1) {
                printf("Invalid input. Please enter only one character.\n");
                validConfirmUsername = 0;
                continue;
            }
            
            switch (confirmUsername[0]) {
                case 'Y':
                case 'y':
                    validConfirmUsername = 1;
                    break;
                case 'N':
                case 'n':
                    validConfirmUsername = 0;
                    break;
                default:
                    printf("Invalid input. Please enter 'Y' or 'N'. \n");
                    validConfirmUsername = 0;
                    break;
            }
        } else {
            isUniqueUsername = 0;
        }
    } while (!validConfirmUsername);
    
    return validConfirmUsername;
}


int ChoosePassword(char* password) {
    char confirmPassword[50];
    int validConfirmPassword = 0;

    do {
        REGISTRATION_HEADER;

        printf("Choose a password : ");
        if (fgets(password, sizeof(password), stdin) == NULL) {
            printf("Error reading password.\n");
            continue;
        }
        password[strcspn(password, "\n")] = '\0'; // Remove newline character

        if (strlen(password) == 0) {
            printf("Password cannot be empty. Please enter a valid password.\n");
            clearInputBuffer();
            continue;
        }

        // Confirm the password
        system("clear");
        printf("Re-enter your password : ");
        if (fgets(confirmPassword, sizeof(confirmPassword), stdin) == NULL) {
            printf("Error reading confirmation.\n");
            continue;
        }
        confirmPassword[strcspn(confirmPassword, "\n")] = '\0'; // Remove newline character

        if (strcmp(confirmPassword, password) == 0) {
            validConfirmPassword = 1;
        } else {
            printf("Passwords do not match. Please try again.\n");
        }

    } while (!validConfirmPassword);
    
    return validConfirmPassword;
}


int ValidUsername(char* username)
{
    FILE* fp = fopen("./data/users.txt", "r");
    struct User userChecker; 

    if (fp == NULL)
    {
        printf("Error opening the users.txt file.\n");
        return 0;
    }

    while (fscanf(fp, "%d %s %s\n", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, username) == 0)
        {
            fclose(fp);
            return 0;
        }
    }

    fclose(fp);
    return 1;
}

int GenerateUniqueId()
{
    FILE* fp = fopen("./data/users.txt", "r");
    int idCounter = 0;
    struct User userChecker; 

    if (fp == NULL)
    {
        printf("Error opening the users.txt file.\n");
        return -1;
    }

    while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) == 3)
    {
        idCounter = MAX(idCounter, userChecker.id);
    }

    fclose(fp);
    return idCounter + 1;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
