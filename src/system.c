#include "header.h"
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define ACCOUNTDETAILS_HEADER do { \
 system("clear"); \
 printf("\n\n\t\t======= Account Details =======\n\n"); \
} while (0)


const char *RECORDS = "./data/records.txt";

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n\n",
            r.id,
        r.userId,
	    r.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit: ");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit: ");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    // printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");
    int validCountry = 1;
    int validPhoneNumber = 1;
    int validAccountType = 1;
    int validDate = 1;
    int validDateFormat = 1;
    int validAmount = 1;
    int validAccountNumber = 1;
    int isUniqueAccountNumber = 1;
    char trimmedPhone[50];


noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");

    /////////////////////////////////////
    //////////// Inputs date ////////////
    /////////////////////////////////////

    if (!validDateFormat) {
        validDate = 1;
        printf("\nInvalid input. Please enter the date in the format mm/dd/yyyy.\n");
    }

    if (!validDate) {
        printf("\nInvalid input. Please enter a valid date.\n");
    }

    // Scans the date and verifies if the format is valid
    printf("\nEnter today's date(mm/dd/yyyy): ");
    if (scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year) != 3) {
        validDateFormat = 0;
        clearInputBuffer();
        goto noAccount;
    }
    validDateFormat = 1;

    // Verifies if the date is valid
    if (r.deposit.month > 12 || r.deposit.day > 31)
    {
        validDate = 0;
        goto noAccount;
    }
    if (r.deposit.month == 2 && r.deposit.day > 29)
    {
        validDate = 0;
        goto noAccount;
    }
    if (r.deposit.month == 4 || r.deposit.month == 6 || r.deposit.month == 9 || r.deposit.month == 11)
    {
        if (r.deposit.day > 30)
        {
            validDate = 0;
            goto noAccount;
        }
    }

    /////////////////////////////////////
    /////// Inputs Account Number ///////
    /////////////////////////////////////

    returnEnterAccountNumber:
    system("clear");
    printf("\t\t\t===== New record =====\n");    

    if (!validAccountNumber) {
        printf("\nInvalid input. Please enter a number.\n");
    }
    if (!isUniqueAccountNumber) {
        printf("\n✖ This Account number already exists. Please enter a unique account number.\n");
    }

    printf("\nEnter the account number: ");
    if (scanf("%d", &r.accountNbr) != 1) {
        isUniqueAccountNumber = 1;
        validAccountNumber = 0;
        clearInputBuffer();
        goto returnEnterAccountNumber;
    }
    validAccountNumber = 1;

    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            fseek(pf, 0, SEEK_SET);
            isUniqueAccountNumber = 0;
            goto returnEnterAccountNumber;
        }
    }

    /////////////////////////////////////
    /////////// Inputs country //////////
    /////////////////////////////////////

    returnEnterCountry:
    system("clear");
    printf("\t\t\t===== New record =====\n");

    clearInputBuffer();

    if (!validCountry) {
        printf("\nInvalid input. Please enter a country.\n");
    }
    printf("\nEnter the country: ");
    if (scanf("%s", r.country) != 1) {
        validCountry = 0;
        clearInputBuffer();
        goto returnEnterCountry;
    }

    clearInputBuffer();

    /////////////////////////////////////
    //////// Inputs Phone number ////////
    /////////////////////////////////////

    returnEnterPhoneNumber:
    system("clear");
    printf("\t\t\t===== New record =====\n");

    if (!validPhoneNumber) {
        printf("\nInvalid input. Please enter a number.\n");
    }
    printf("\nEnter the phone number: ");
    if (fgets(r.phone, sizeof(r.phone), stdin) == NULL) {
        validPhoneNumber = 0;
        goto returnEnterPhoneNumber;
        }

    r.phone[strcspn(r.phone, "\n")] = '\0'; // Remove newline character

    if (!isValidPhoneNumber(r.phone)) {
        validPhoneNumber = 0;
        goto returnEnterPhoneNumber;
    }

    validPhoneNumber = 1;

    /////////////////////////////////////
    ////// Inputs Amount to Deposit /////
    /////////////////////////////////////

    returnEnterAmountToDeposit:
    system("clear");
    printf("\t\t\t===== New record =====\n");

    if (!validAmount) {
        printf("\nInvalid input. Please enter a number.\n");
    }
    printf("\nEnter amount to deposit: $");
    if (scanf("%lf", &r.amount) != 1 || r.amount < 0) {
        validAmount = 0;
        clearInputBuffer();
        goto returnEnterAmountToDeposit;
    }

    /////////////////////////////////////
    //////// Inputs Account Type ////////
    /////////////////////////////////////

    returnEnterAccountType:
    system("clear");
    printf("\t\t\t===== New record =====\n");

    if (!validAccountType) {
        printf("\nInvalid input. Please enter a valid account type.\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice: ");
    }
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice: ");
    scanf("%s", r.accountType);

    if (strcmp(r.accountType, "saving") != 0 && strcmp(r.accountType, "current") != 0 && strcmp(r.accountType, "fixed01") != 0 && strcmp(r.accountType, "fixed02") != 0 && strcmp(r.accountType, "fixed03") != 0)
    {
        validAccountType = 0;
        goto returnEnterAccountType;
    }

    // Generetes a unique id for the account and saves the account to the file
    r.userId = u.id;
    strcpy(r.name, u.name);
    r.id = GenerateUniqueIdAccount();
    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%s \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}

int GenerateUniqueIdAccount()
{
    FILE* fp = fopen("./data/records.txt", "r");
    int idCounter = 0;
    struct Record r; 

    if (fp == NULL)
    {
        printf("Error opening the users.txt file.\n");
        return -1;
    }

    while (fscanf(fp, "%d %d %s %d %d/%d/%d %s %s %lf %s",
                  &r.id,
		  &r.userId,
		  r.name,
                  &r.accountNbr,
                  &r.deposit.month,
                  &r.deposit.day,
                  &r.deposit.year,
                  r.country,
                  r.phone,
                  &r.amount,
                  r.accountType) == 11)
    {
        idCounter = MAX(idCounter, r.id);
    }

    fclose(fp);
    return idCounter + 1;
}

void CheckAccountDetails(struct User u)
{
    int accountNumber;
    int notGood = 0;
    struct Record r;
    FILE *pf = fopen(RECORDS, "r");

    ACCOUNTDETAILS_HEADER;
    printf("Enter the account number: ");
    scanf("%d", &accountNumber);

    while (getAccountFromFile(pf, r.name, &r))
    {
        if (r.accountNbr == accountNumber && strcmp(r.name, u.name) == 0)
        {
            double interest = CalculateInterest(r.amount, r.accountType);
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%s \nAmount deposited: $%.2f \nType Of Account:%s\n\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
            if (strcmp(r.accountType, "saving") == 0) {
                printf("You will get $%.2f as interest on day %d of every month\n", interest, r.deposit.day);
            }
            if (strcmp(r.accountType, "current") == 0) {
                printf("You will not get interests because the account is of type current");
            }
            if (strcmp(r.accountType, "fixed01") == 0) {
                printf("You will get $%.2f as interest the %d/%d/%d", interest, r.deposit.day, r.deposit.month, r.deposit.year + 1);
            }
            if (strcmp(r.accountType, "fixed02") == 0) {
                printf("You will get $%.2f as interest the %d/%d/%d", interest, r.deposit.day, r.deposit.month, r.deposit.year + 2);
            }
            if (strcmp(r.accountType, "fixed03") == 0) {
                printf("You will get $%.2f as interest the %d/%d/%d", interest, r.deposit.day, r.deposit.month, r.deposit.year + 3);
            }

            notGood = 1;
            break;
        }
    }
    fclose(pf);
    stayOrReturn(notGood, CheckAccountDetails, u);
}

double CalculateInterest(double amount, char accountType[10])
{
    double interest = 0;
    if (strcmp(accountType, "saving") == 0)
    {
        interest = amount * 0.07;
    }
    else if (strcmp(accountType, "current") == 0)
    {
        interest = amount;
    }
    else if (strcmp(accountType, "fixed01") == 0)
    {
        interest = amount * 0.04;
    }
    else if (strcmp(accountType, "fixed02") == 0)
    {
        interest = amount * 0.05 * 2;
    }
    else if (strcmp(accountType, "fixed03") == 0)
    {
        interest = amount * 0.08 * 3;
    }
    return interest;
}

int getAccountFromFile(FILE *fp, char *username, struct Record *r)
{
    if (fscanf(fp, "%d %d %s %d %d/%d/%d %s %s %lf %s",
               &r->id,
               &r->userId,
               r->name,
               &r->accountNbr,
               &r->deposit.month,
               &r->deposit.day,
               &r->deposit.year,
               r->country,
               r->phone,
               &r->amount,
               r->accountType) == EOF)
    {
        return 0;
    }

    strcpy(username, r->name);
    return 1;
}

int isValidPhoneNumber(char *phone)
{
    if (phone[0] != '+' && !isDigit(phone[0])) {
        return 0;
    }

    for (int i = 1; phone[i] != '\0'; i++) {
        if (!isDigit(phone[i])) {
            return 0;
        }
    }

    return 1;
}

int isDigit(char c) {
    return c >= '0' && c <= '9';
}