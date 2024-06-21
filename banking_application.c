

#include <string.h>
#include <time.h>


#define CUSTOMER_FILE "customer.dat"
#define ACCOUNT_FILE "account_details.dat"
#define TRANSACTION_FILE "Deposit_Withdraw.dat"
#define MAX_STRING_LENGTH 100#include <stdio.h>
#include <stdlib.h>
#include <st


// Define structures for customer, account, and transaction
struct Customer {
    char id[10]; // Increase by 1 to accommodate null terminator
    char name[MAX_STRING_LENGTH];
    char address[MAX_STRING_LENGTH];
    char mobile[12]; // Increase by 1 to accommodate null terminator
};


struct Account {
    char id[10]; // Increase by 1 to accommodate null terminator
    char number[17]; // Increase by 1 to accommodate null terminator
    char type[4]; // Increase by 1 to accommodate null terminator
    float balance;
    char account_buffer[20];
};


struct Transaction {
    char account_number[17]; // Increase by 1 to accommodate null terminator
    char date[12]; // Increase by 1 to accommodate null terminator
    float amount;
    char type[9]; // Increase by 1 to accommodate null terminator
};


// Function prototypes
int login();
void staffMenu();
void addCustomer();
void addAccount();
void deposit();
void withdraw();
void balanceEnquiry();
void loanApprovals();
void logoff();


int main() {
    int loginSuccess = login();
    if (!loginSuccess) {
        printf("Login failed. Exiting...\n");
        return 1;
    }


    staffMenu();


    return 0;
}


int login() {
   
    char username[MAX_STRING_LENGTH], password[MAX_STRING_LENGTH];
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove trailing newline
    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove trailing newline


    // Assuming staff credentials are stored in a flat file
    FILE *fp = fopen("staff_credentials.dat", "r");
    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return 0;
    }


    char file_username[MAX_STRING_LENGTH], file_password[MAX_STRING_LENGTH];
    while (fscanf(fp, "%s %s", file_username, file_password) != EOF) {
        if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0) {
            printf("Login successful!\n");
            printf("WELCOME TO AUBE BANK SYSTEM \n");
            fclose(fp);
            return 1;
        }
    }


    fclose(fp);
    return 0;
}


void staffMenu() {
    int choice;
   
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("Date and time of login : %d-%02d-%02d %02d:%02d:%02d\n",
           tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
           tm.tm_hour, tm.tm_min, tm.tm_sec);


    do {
        printf("\nStaff Menu\n");
        printf("1. Add a Customer\n");
        printf("2. Add an Account\n");
        printf("3. Deposit\n");
        printf("4. Withdrawal\n");
        printf("5. Balance Enquiry\n");
        printf("6. Loan Approvals\n");
        printf("0. Logoff\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character


        switch (choice) {
            case 1:
                addCustomer();
                break;
            case 2:
                addAccount();
                break;
            case 3:
                deposit();
                break;
            case 4:
                withdraw();
                break;
            case 5:
                balanceEnquiry();
                break;
            case 6:
                loanApprovals();
                break;
            case 0:
                printf("Logging Out....\n");
                break; // exiting the program
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}


void addCustomer() {
    FILE *file = fopen(CUSTOMER_FILE, "a");
    if (file == NULL) {
        printf("Error: Unable to open customer file.\n");
        return;
    }


    struct Customer newCustomer;
    printf("Enter customer ID: ");
    fgets(newCustomer.id, sizeof(newCustomer.id), stdin);
    newCustomer.id[strcspn(newCustomer.id, "\n")] = '\0'; // Remove trailing newline
    printf("Enter customer name: ");
    fgets(newCustomer.name, sizeof(newCustomer.name), stdin);
    newCustomer.name[strcspn(newCustomer.name, "\n")] = '\0'; // Remove trailing newline
    printf("Enter customer address: ");
    fgets(newCustomer.address, sizeof(newCustomer.address), stdin);
    newCustomer.address[strcspn(newCustomer.address, "\n")] = '\0'; // Remove trailing newline
    printf("Enter customer mobile: ");
    fgets(newCustomer.mobile, sizeof(newCustomer.mobile), stdin);
    newCustomer.mobile[strcspn(newCustomer.mobile, "\n")] = '\0'; // Remove trailing newline


    fprintf(file, "%8s %20s %50s %10s\n", newCustomer.id, newCustomer.name, newCustomer.address, newCustomer.mobile);
    fclose(file);
    printf("Customer added successfully.\n");
}


void addAccount() {
    FILE *customerFile = fopen(CUSTOMER_FILE, "r");
    if (customerFile == NULL) {
        printf("Error: Unable to open customer file.\n");
        return;
    }
    else
    {
        printf("Please enter the following details : \n");
    }


    char customerID[10]; // Increase by 1 to accommodate null terminator
    printf("Enter customer ID: ");
    fgets(customerID, sizeof(customerID), stdin);
    customerID[strcspn(customerID, "\n")] = '\0'; // Remove trailing newline




    // Search for the customer in the customer file


    fseek(customerFile, 0, SEEK_SET);


    char buffer[10];
    struct Customer customer;
    int customerFound = 0;
    char holdarea[sizeof(struct Customer)];
    char custid[10];
    while (fscanf(customerFile, "%8s %*s %*s %*s", holdarea) == 1)
    {
        printf("searching customer !!!!  %s\n", holdarea);    
        sprintf(custid, "%s", holdarea);


        if (strcmp(custid, customerID) == 0) {
            customerFound = 1;
            printf("Customer with ID %s found.\n", customerID);
            break;
        }
    }
       
    fclose(customerFile);


    if (!customerFound) {
        printf("Customer with ID %s not found.\n", customerID);
        return;
    }


    // Proceed to add account details
    FILE *accountFile = fopen(ACCOUNT_FILE, "a");
    if (accountFile == NULL) {
        printf("Error: Unable to open account file.\n");
        return;
    }


    // Prompt for account details
    struct Account newAccount;
    strcpy(newAccount.id, customerID);
    printf("Enter account number: ");
    fgets(newAccount.number, sizeof(newAccount.number), stdin);
    newAccount.number[strcspn(newAccount.number, "\n")] = '\0'; // Remove trailing newline
    printf("Enter account type (SB, CA, RD, FD): ");
    fgets(newAccount.type, sizeof(newAccount.type), stdin);
    newAccount.type[strcspn(newAccount.type, "\n")] = '\0'; // Remove trailing newline
    printf("Enter opening balance: ");
    scanf("%f", &newAccount.balance);


    // Append account details to account file
    fprintf(accountFile, "%8s %15s %2s %10.2f \n", newAccount.id, newAccount.number, newAccount.type, newAccount.balance);
    fclose(accountFile);


    printf("Account added successfully for customer with ID %s.\n", customerID);
}


void deposit()
{


    char account_number[17];
    float amount;
   


    FILE *accountFile = fopen(ACCOUNT_FILE, "rb+");
    if (accountFile == NULL) {
        printf("Error: Unable to open account file.\n");
        return;
    }
    else
    {
        printf("Please Enter the following details \n");
    }


    // char account_number[10]; // Increase by 1 to accommodate null terminator
    printf("Enter account number : ");
    fgets(account_number, sizeof(account_number), stdin);
    account_number[strcspn(account_number, "\n")] = '\0'; // Remove trailing newline
    printf("Enter deposit amount: ");
    scanf("%f", &amount);


    // Search for account_number in the account file


    fseek(accountFile, 0, SEEK_SET);


    char buffer[10];


   
    struct Account account;
    int found = 0;
 


    char holdarea1 [sizeof(struct Transaction)];
    char accnum[10];
    int no_of_rec = 0;
   
    char custId[20];
    char accName[20];
    char accType[3];
    double account_balance;
    char accBuff[20];
   
    int pos1=0, pos2=0;
    while (fscanf(accountFile, "%8s %15s %2s %lf", custId, accName, accType, &account_balance)) { //fscanf = reads from file , holdarea = variable
       
        pos1=pos2;
        pos2=ftell(accountFile);


        printf("pos 1 : %d pos 2 : %d", pos1, pos2);
        char pos[10];
        printf("%s %s %s %.2f\n", custId, accName, accType, account_balance);
       
        printf("Account Number : %s\n", accName);
        if (strcmp(accName, account_number) == 0) {
            found = 1;
            printf("Account number %s found.\n", account_number);


            // Update balance
            printf("Current balance : %.2f\n", account_balance);
            printf("Transaction : %.2f\n", amount);
            account_balance += amount;
            printf("New balance : %.2f\n", account_balance);
            printf("%ld\n", ftell(accountFile));
           
            if (pos1 == 0) {
                fseek(accountFile, pos1, SEEK_SET);
            } else {
                fseek(accountFile, pos1+1, SEEK_SET);
            }
           
            //fseek(accountFile, -sizeof(struct Account)*no_of_rec, SEEK_SET);
           
                       
            printf("%ld\n", ftell(accountFile));


            fprintf(accountFile, "\n%8s %15s %2s %10.2f", custId, accName, accType, account_balance);
            //fwrite(&account, sizeof(struct Transaction), 1, accountFile);




            // Log transaction
            FILE *transactionFile = fopen(TRANSACTION_FILE, "a");
            if (transactionFile == NULL)
            {
                printf("Error: Unable to open transaction file.\n");
                return;
            }
            struct Transaction transaction;
            strcpy(transaction.account_number, account_number);
            strcpy(transaction.type, "Deposit");
 
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            char datebuffer[10];
            sprintf(datebuffer, "%d-%02d-%02d",
                    tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
               
            strcpy(transaction.date, datebuffer); // You may need to replace this with the actual date
            transaction.amount = amount;


            fprintf(transactionFile, "%s %s %.2f %s\n", transaction.account_number, transaction.date, transaction.amount, transaction.type);


            //fwrite(&transaction, sizeof(struct Transaction), 1, transactionFile);
            fclose(transactionFile);
           
            printf("Deposit successful.\n");


            break;
        }
    }
       
   
    fclose(accountFile);
}


void withdraw()
{


    char account_number[17];
    float amount;
   


    FILE *accountFile = fopen(ACCOUNT_FILE, "rb+");
    if (accountFile == NULL) {
        printf("Error: Unable to open account file.\n");
        return;
    }
    else
    {
        printf("Please Enter the following details :\n");
    }


    // char account_number[10]; // Increase by 1 to accommodate null terminator
    printf("Enter account number : ");
    fgets(account_number, sizeof(account_number), stdin);
    account_number[strcspn(account_number, "\n")] = '\0'; // Remove trailing newline
    printf("Enter withdrawal amount: ");
    scanf("%f", &amount);


    // Search for account_number in the account file


    fseek(accountFile, 0, SEEK_SET);


    char buffer[10];


   
    struct Account account;
    int found = 0;
 


    char holdarea1 [sizeof(struct Transaction)];
    char accnum[10];
    int no_of_rec = 0;
   
    char custId[20];
    char accName[20];
    char accType[3];
    double account_balance;
    char accBuff[20];
   
    int pos1=0, pos2=0;
    while (fscanf(accountFile, "%8s %15s %2s %lf", custId, accName, accType, &account_balance))
    { //fscanf = reads from file , holdarea = variable
       
        pos1=pos2;
        pos2=ftell(accountFile);


        char pos[10];
        if (strcmp(accName, account_number) == 0) {
            found = 1;
            printf("Account number %s found.\n", account_number);
            if (account_balance >= amount) {
                // Update balance
                printf("Current balance : %.2f\n", account_balance);
                printf("Transaction : %.2f\n", amount);
                account_balance -= amount;
                printf("New balance : %.2f\n", account_balance);
                printf("%ld\n", ftell(accountFile));
               
                if (pos1 == 0) {
                    fseek(accountFile, pos1, SEEK_SET);
                } else {
                    fseek(accountFile, pos1+1, SEEK_SET);
                }
               
                //fseek(accountFile, -sizeof(struct Account)*no_of_rec, SEEK_SET);
               
                       
                printf("%ld\n", ftell(accountFile));


                fprintf(accountFile, "%8s %15s %2s %10.2f", custId, accName, accType, account_balance);
                //fwrite(&account, sizeof(struct Transaction), 1, accountFile);




                // Log transaction
                FILE *transactionFile = fopen(TRANSACTION_FILE, "a");
                if (transactionFile == NULL)
                {
                    printf("Error: Unable to open transaction file.\n");
                    return;
                }
                struct Transaction transaction;
                strcpy(transaction.account_number, account_number);
                strcpy(transaction.type, "Withdraw");
   
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                char datebuffer[10];
                sprintf(datebuffer, "%d-%02d-%02d",
                        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
                   
                strcpy(transaction.date, datebuffer); // You may need to replace this with the actual date
                transaction.amount = amount;


                fprintf(transactionFile, "%s %s %.2f %s\n", transaction.account_number, transaction.date, transaction.amount, transaction.type);


                //fwrite(&transaction, sizeof(struct Transaction), 1, transactionFile);
                fclose(transactionFile);
               
                printf("Withdrawal successful.\n");
                break;
            } else {
                printf("Account balance is not sufficient for this withdrawal.\n");


            }
        }
    }


    fclose(accountFile);


}


void balanceEnquiry() {


    char account_number[17];
   


    FILE *accountFile = fopen(ACCOUNT_FILE, "rb+");
    if (accountFile == NULL) {
        printf("Error: Unable to open account file.\n");
        return;
    }
    else
    {
        printf("Please Enter the following details :\n");
    }


    // char account_number[10]; // Increase by 1 to accommodate null terminator
    printf("Enter account number : ");
    fgets(account_number, sizeof(account_number), stdin);
    account_number[strcspn(account_number, "\n")] = '\0'; // Remove trailing newline


    // Search for account_number in the account file


    fseek(accountFile, 0, SEEK_SET);


    char buffer[10];


   
    struct Account account;
    int found = 0;
 


    char holdarea1 [sizeof(struct Transaction)];
    char accnum[10];
    int no_of_rec = 0;
   
    char custId[20];
    char accName[20];
    char accType[3];
    double account_balance;
    char accBuff[20];
   
    int pos1=0, pos2=0;
    while (fscanf(accountFile, "%8s %15s %2s %lf", custId, accName, accType, &account_balance))
    { //fscanf = reads from file , holdarea = variable
       
        pos1=pos2;
        pos2=ftell(accountFile);


        char pos[10];
        printf("%s %s %s %.2f\n", custId, accName, accType, account_balance);
       
        printf("Account Number : %s\n", accName);
        if (strcmp(accName, account_number) == 0)
        {
            found = 1;
            printf("Account number %s found.\n", account_number);
            if (account_balance >= 1000.00)
            {
                // Update balance
                printf("Current balance : %.2f\n", account_balance);
                break;
            }
            else
            {
                printf("Insufficient FUnds");
            }
            break;
        }
   
    }
    fclose(accountFile);
}


void loanApprovals()
{
    int ac;
    char type_of_loan[50];


    printf("Enter Account Number: \n");
    scanf("%d", &ac);
    getchar();
    printf("Types of Loans: \n");
    printf("1. Personal Loan \n");
    printf("2. Credit Card Loan \n");
    printf("3. Education Loan \n");
    printf("4. Short-term Business Loan \n");
    printf("5. Payday Loan \n");
    printf("6. Flexi Loans \n");
    printf("Enter type of loan: \n");
    fgets(type_of_loan, sizeof(type_of_loan), stdin);
    printf("Account Number: %d\n", ac);
    printf("Type of Loan: %s", type_of_loan);
    printf("Loan Request for account number %d for %s has been placed.", ac, type_of_loan);
}





