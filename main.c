#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 10
#define MAX_USERNAME_LEN 20
#define MAX_PASSWORD_LEN 20

struct Account {
  char username[MAX_USERNAME_LEN + 1];
  char password[MAX_PASSWORD_LEN + 1];
  double balance;
};

int login(struct Account accounts[], int numAccounts);
void doDeposit(struct Account *account);
void doWithdraw(struct Account *account);
void printMenu(struct Account *account);

int main(int argc, char *argv[]) {
  struct Account accounts[MAX_ACCOUNTS];
  int numAccounts = 0;
  int option;

  FILE *file = fopen("accounts.txt", "r");
  if (file == NULL) 
  {
    printf("Error opening accounts file.\n");
    return 1;
  }
  while (fscanf(file, "%s %s %lf", accounts[numAccounts].username, accounts[numAccounts].password, &accounts[numAccounts].balance) == 3) 
  {
    numAccounts++;
  }
  fclose(file);

  int loggedIn = 0;
  int accountIndex;
  while (!loggedIn) 
  {
    accountIndex = login(accounts, numAccounts);
    if (accountIndex >= 0) 
    {
      loggedIn = 1;
    }
  }

  while (1) {
    printMenu(&accounts[accountIndex]);
    scanf("%d", &option);

    switch (option) 
    {
      case 1:
        doDeposit(&accounts[accountIndex]);
        break;
      case 2:
        doWithdraw(&accounts[accountIndex]);
        break;
      case 3:
        file = fopen("accounts.txt", "w");
        if (file == NULL) 
        {
          printf("Error opening accounts file.\n");
          return 1;
        }
        for (int i = 0; i < numAccounts; i++) 
        {
          fprintf(file, "%s %s %.2lf\n", accounts[i].username, accounts[i].password, accounts[i].balance);
        }
        fclose(file);
        printf("Goodbye!\n");
        return 0;
        break;
      default:
        printf("Invalid option.\n");
        break;
    }
  }
}

int login(struct Account accounts[], int numAccounts) 
{
      char username[MAX_USERNAME_LEN + 1];
      char password[MAX_PASSWORD_LEN + 1];
    
      printf("Enter username: ");
      scanf("%s", username);
      printf("Enter password: ");
      scanf("%s", password);
    
      for (int i = 0; i < numAccounts; i++) 
      {
        if (strcmp(username, accounts[i].username) == 0 && strcmp(password, accounts[i].password) == 0) 
        {
            printf("Welcome, %s!\n", username);
            return i;
        }

        }

    printf("Invalid username or password.\n");
    return -1;
}

void doDeposit(struct Account *account) 
{
    double amount;
    printf("Enter amount to deposit: ");
    scanf("%lf", &amount);
    account->balance += amount;
    printf("Deposited $%.2lf. New balance: $%.2lf.\n", amount, account->balance);
}

void doWithdraw(struct Account *account) 
{
    double amount;
    printf("Enter amount to withdraw: ");
    scanf("%lf", &amount);
    if (amount > account->balance) 
    {
        printf("Insufficient funds.\n");
    } 
    else 
    {
        account->balance -= amount;
        printf("Withdrew $%.2lf. New balance: $%.2lf.\n", amount, account->balance);
    }
}

void printMenu(struct Account *account) 
{
    printf("\nMenu:\n");
    printf("1. Deposit\n");
    printf("2. Withdraw\n");
    printf("3. Exit\n");
    printf("Current balance: $%.2lf\n", account->balance);
    printf("Enter option: ");
}
