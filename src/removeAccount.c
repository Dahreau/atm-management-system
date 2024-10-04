#include "header.h"

#define REMOVE_HEADER do { \
 system("clear"); \
 printf("\n\n\t\t======= Remove Account =======\n\n"); \
} while (0)

const char *RECORDS2 = "./data/records.txt";

void RemoveAccount(struct User u)
{
    int accountNumber;
    int notGood = 0;
    struct Record r;
    FILE *pf = fopen(RECORDS2, "r");

    REMOVE_HEADER;
    printf("Enter the account number:");
    scanf("%d", &accountNumber);

    FILE *tempFile = fopen("./data/temp_records.txt", "w");

    while (getAccountFromFile(pf, r.name, &r))
    {
        if (r.accountNbr == accountNumber && r.userId == u.id)
        {
            notGood = 1;
            continue;
        }
        saveAccountToFile(tempFile, u, r);
    }

    fclose(pf);
    fclose(tempFile);

    remove("./data/records.txt");
    rename("./data/temp_records.txt", "./data/records.txt");

    if (notGood)
    {
        printf("Account removed successfully.\n");
    }
    else
    {
        printf("Account ID not found.\n");
    }
    success(u);
}