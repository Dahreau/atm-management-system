#include "header.h"
#define TRANSACTION_HEADER do { \
 system("clear"); \
 printf("\n\n\t\t======= Transaction =======\n\n"); \
} while (0)

    const char *RECORDS1 = "./data/records.txt";
    int accountNumber;
    double currentAmount;

void MakeTransaction(struct User u)
{
    int notGood = 0;
    struct Record r;
    FILE *pf = fopen(RECORDS1, "r");
    int option;

    TRANSACTION_HEADER;
    printf("Enter the account number: ");
    scanf("%d", &accountNumber);

    while (getAccountFromFile(pf, r.name, &r))
    {
        TRANSACTION_HEADER;
        if (r.accountNbr == accountNumber && strcmp(r.name, u.name) == 0)
        {
            // Check if the account is fixed01, fixed02, or fixed03
            if (strcmp(r.accountType, "fixed01") == 0 || strcmp(r.accountType, "fixed02") == 0 || strcmp(r.accountType, "fixed03") == 0) {
                printf("Transactions are not allowed for fixed accounts.\n");
                notGood = 1;
                break;
            }
            printf("\n\t\t-->> Current Balance : $%.2f <<--\n", r.amount);
            printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
            printf("\n\t\t[1]- Deposit\n");
            printf("\n\t\t[2]- Withdraw\n");
            printf("\n\t\t[3]- Exit\n");
            scanf("%d", &option);

                switch (option)
                {
                case 1:
                    Deposit(u);
                    break;
                case 2:
                    Withdraw(u);
                    break;
                case 3:
                    mainMenu(u);
                    break;
                default:
                    printf("Invalid operation!\n");
                }
                notGood=1;
                break;
            }
        }
    fclose(pf);
    stayOrReturn(notGood, MakeTransaction, u);
    }

void Deposit(struct User u)
{
    double amount;
    int option;
    struct Record r;

    FILE *pf = fopen(RECORDS1, "r");

        if (pf == NULL)
    {
        printf("Error opening the records.txt file.\n");
        return;
    }
    
    TRANSACTION_HEADER;
            FILE *tempFile = fopen("./data/temp_records.txt", "w");
        while (getAccountFromFile(pf, r.name, &r)) {

            if (r.accountNbr == accountNumber && r.userId == u.id)
        {

            printf("Current balance : $%.2f", r.amount);
            printf("\nEnter the amount to deposit: $");
            scanf("%lf", &amount);

            r.amount += amount;
            currentAmount = r.amount;
        
            // Write updated record to temp file
            saveAccountToFile(tempFile, u, r);
        } else {
            // Write unchanged record to temp file
            saveAccountToFile(tempFile, u, r);
        }
}
            fclose(pf);
            fclose(tempFile);

            remove("./data/records.txt");
            rename("./data/temp_records.txt", "./data/records.txt");
            printf("Deposit successful. Current balance : $%.2f\n", currentAmount);
            success(u);

}

void Withdraw(struct User u)
{
    double amount;
    int option;
    struct Record r;
    int notGood = 0;
    int optionRetry = 1;
    int optionRetryFormat = 1;

    FILE *pf = fopen(RECORDS1, "r");

        if (pf == NULL)
    {
        printf("Error opening the records.txt file.\n");
        return;
    }
    
    TRANSACTION_HEADER;
            FILE *tempFile = fopen("./data/temp_records.txt", "w");
        while (getAccountFromFile(pf, r.name, &r)) {

            if (r.accountNbr == accountNumber && r.userId == u.id)
        {

            printf("Current balance : $%.2f", r.amount);
            printf("\nEnter the amount to withdraw: $");
            scanf("%lf", &amount);

            if (amount > r.amount)
            {
                retryOptionRetry:
                TRANSACTION_HEADER;

                if (!optionRetry) {
                    printf("Invalid operation!\n");
                }
                {
                printf("Insufficient funds.\n");
                printf("\n\t\t[1] Retry\n");
                printf("\n\t\t[2] Return to Menu\n");
                printf("\n\t\t[3] Exit\n");

                if (scanf("%d", &option) != 1) {
                    clearInputBuffer();
                    optionRetryFormat = 0;
                    optionRetry = 1;
                    goto retryOptionRetry;
                }

                switch (option)
                {
                    case 1:
                        optionRetry = 1;
                        Withdraw(u);
                        break;
                    case 2:
                        optionRetry = 1;
                        mainMenu(u);
                        break;
                    case 3:
                        optionRetry = 1;
                        exit(0);
                        break;
                    default:
                        optionRetry = 0;
                        goto retryOptionRetry;
                }
                }

            }
            r.amount -= amount;
            currentAmount = r.amount;
        
        // Write updated record to temp file
            saveAccountToFile(tempFile, u, r);
        } else {
            // Write unchanged record to temp file
            saveAccountToFile(tempFile, u, r);
        }

}
            fclose(pf);
            fclose(tempFile);
            
            remove("./data/records.txt");
            rename("./data/temp_records.txt", "./data/records.txt");
            TRANSACTION_HEADER;
            printf("Withdrawal successful. Current balance : $%.2f\n", currentAmount);
            success(u);
}

