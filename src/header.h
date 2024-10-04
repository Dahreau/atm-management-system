#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    char phone[50];
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

// authentication functions
void loginMenu(char a[50], char pass[50]);
void registerMenu(char a[50], char pass[50]);
const char *getPassword(struct User *u);

// system function
int isSameUser(struct User loggedInUser, struct User targetUser);
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
void Registration(struct User *u);
int ChooseUsername(char username[]);
int ChoosePassword(char password[]);
int GenerateUniqueId();
int GenerateUniqueIdAccount();
int ValidUsername(char* username);
void clearPasswordInput();
void clearInputBuffer();
void updateAccount(struct User u);
int getAccountFromFile(FILE *ptr, char name[50], struct Record *r);
void saveAccountToFile(FILE *ptr, struct User u, struct Record r);
void CheckAccountDetails(struct User u);
double CalculateInterest(double amount, char accountType[10]);
void MakeTransaction(struct User u);
void Deposit(struct User u);
void Withdraw(struct User u);
void stayOrReturn(int notGood, void f(struct User u), struct User u);
void success(struct User u);
void RemoveAccount(struct User u);
void TransferAccount(struct User u);
int isValidPhoneNumber(char *phone);
int isDigit(char c);





#endif