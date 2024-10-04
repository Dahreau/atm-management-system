#include "header.h"
#define UPDATE_HEADER do { \
 system("clear"); \
 printf("\n\n\t\t======= Update Account Information =======\n\n"); \
} while (0)

extern struct User currentUser;

void updateAccount(struct User u)
{
    FILE *fp = fopen("./data/records.txt", "r+");

    if (fp == NULL)
    {
        printf("Error opening the records.txt file.\n");
        return;
    }


    int idToUpdate;
    struct Record r;
    int found = 0;
    int option;
    char newCountry[50];
    char newPhone[50];
    int validNewCountry = 0;
    int validUpdateOption = 1;
    int validAccountIDtoUpdate = 1;
    int validNewPhone = 1;
    int retypeNewCountry = 1;

    UPDATE_HEADER;

    accountnumber:
    if (!validAccountIDtoUpdate) {
        printf("Invalid account ID.\n");
    }
    remove("./data/temp_records.txt");
    rewind(fp);
    FILE *tempFile = fopen("./data/temp_records.txt", "w");

    if (tempFile == NULL)
    {
        printf("Error opening the temp_records.txt file.\n");
        fclose(fp);
        return;
    }
    printf("\nEnter the account ID to update: ");
    clearInputBuffer();
    if(scanf("%d", &idToUpdate) != 1) {
        validAccountIDtoUpdate = 0;
        UPDATE_HEADER;
        goto accountnumber;
    }
    while (getAccountFromFile(fp, r.name, &r)) {

        if (r.accountNbr == idToUpdate && r.userId == u.id)
        {


            found = 1;
            
            retypeUpdateChoice:
            UPDATE_HEADER;
            if (!validUpdateOption) {
                printf("Invalid input.\n");
            }
            printf("\n\t\t[0]- Return to main menu\n");
            printf("\n\t\t[1]- Change country\n");
            printf("\n\t\t[2]- Change phone number\n");
            if (scanf("%d", &option) != 1) {
                validUpdateOption = 0;

                clearInputBuffer();
                goto retypeUpdateChoice;
            }

            switch (option)
            {
            case 0:
                mainMenu(u);
                break;
            case 1 :
                do {
                    // retypeNewCountry:
                    UPDATE_HEADER;
                    printf("\nEnter new country: ");
                    clearInputBuffer();
                    if (fgets(newCountry, sizeof(newCountry), stdin) == NULL) {
                        printf("Error reading input.\n");
                        validNewCountry = 0;
                        // goto retypeNewCountry;
                    } else {
                        newCountry[strcspn(newCountry, "\n")] = 0; // Remove newline character
                        validNewCountry = 1; // Add validation logic if needed
                        strcpy(r.country, newCountry);

                    }
                } while (!validNewCountry);
                break;
            case 2 :
                // UPDATE_HEADER;
                retypeNewPhone:
                UPDATE_HEADER;
                if (!validNewPhone) {
                    printf("Invalid phone number.\n");
                }
                printf("\nEnter new phone number: ");
                clearInputBuffer();
                if (fgets(newPhone, sizeof(newPhone), stdin) == NULL) {
                    printf("Error reading input.\n");
                    validNewPhone = 0;
                    clearInputBuffer();
                    goto retypeNewPhone;
                } else {
                    newPhone[strcspn(newPhone, "\n")] = 0; // Remove newline character
                    validNewPhone = 1; // Add validation logic if needed
                strcpy(r.phone, newPhone);
                }
                break;
            default:
                printf("Invalid option.\n");
                // fclose(fp);
                // fclose(tempFile);
                goto retypeUpdateChoice;
                // return;
            }

            // Write updated record to temp file
            saveAccountToFile(tempFile, u, r);
        } else {
            // Write unchanged record to temp file
            saveAccountToFile(tempFile, u, r);
        }
    }

    if (!found) {
        validAccountIDtoUpdate = 1;
        UPDATE_HEADER;
        printf("Account ID not found.\n");
        goto accountnumber;
    }

    fclose(fp);
    fclose(tempFile);

    // Replace original file with updated temp file
    remove("./data/records.txt");
    rename("./data/temp_records.txt", "./data/records.txt");

    printf("Account information updated successfully.\n");
    success(u);
}


