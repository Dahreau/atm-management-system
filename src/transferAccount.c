#include "header.h"
#define TRANSFER_HEADER do { \
 system("clear"); \
 printf("\n\n\t\t======= Transfer =======\n\n"); \
} while (0)

const char *RECORDS3 = "./data/records.txt";

void TransferAccount(struct User u)
{
    int accountNumber;
    int notGood = 0;
    struct Record r;
    FILE *pf = fopen(RECORDS3, "r");
    if (pf == NULL)
    {
        printf("Error opening the records.txt file.\n");
        return;
    }

    FILE *tempFile = fopen("./data/temp_records.txt", "w");

    if (tempFile == NULL)
    {
        printf("Error opening the temp_records.txt file.\n");
        fclose(pf);
        return;
    }

    TRANSFER_HEADER;
    printf("Enter the account number you want to transfer: ");
    scanf("%d", &accountNumber);

    while (getAccountFromFile(pf, r.name, &r))
    {
        if (r.accountNbr == accountNumber && r.userId == u.id)
        {
            // Gets the username
            clearInputBuffer();
            printf("Enter the username of the user you want to transfer the account to: ");
            char username[50];
            if (fgets(username, 50, stdin) == NULL) {
                printf("Error reading username.\n");
                continue;
            }
            username[strcspn(username, "\n")] = '\0'; // Remove newline character

            // Prevents empty username
            if(strlen(username) == 0) {
                printf("Invalid username.\n");
                continue;
            }

            struct User targetUser;
            FILE *fp = fopen("./data/users.txt", "r");
            int found = 0;
            while (fscanf(fp, "%d %s %s\n", &targetUser.id, targetUser.name, targetUser.password) != EOF)
            {
                if (strcmp(targetUser.name, username) == 0)
                {
                    found = 1;
                    break;
                }
            }

            if (found)
            {
                r.userId = targetUser.id;
                strcpy(r.name, targetUser.name);
                // saveAccountToFile(tempFile, targetUser, r);
                printf("Account transferred successfully.\n");
            }
            else
            {
                printf("User not found.\n");
            }
            notGood = 1;
            // break;
        }
        // Write the record to the temporary file, whether it was transferred or not
        saveAccountToFile(tempFile, u, r);
    }
    fclose(pf);
    fclose(tempFile);
    remove("./data/records.txt");
    rename("./data/temp_records.txt", "./data/records.txt");

    printf("Account transfer successful.\n");
    success(u);
}