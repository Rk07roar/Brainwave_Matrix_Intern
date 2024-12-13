#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class Account {
public:
    string accountHolder;
    int accountNumber;
    double balance;

    Account(string holder, int number, double initialBalance) {
        accountHolder = holder;
        accountNumber = number;
        balance = initialBalance;
    }
};

class HashTable {
private:
    vector<Account*> table;
    int tableSize;

    int hashFunction(int accountNumber) {
        return accountNumber % tableSize;
    }

public:
    HashTable(int size) {
        tableSize = size;
        table.resize(size, nullptr);
    }

    void insert(Account* account) {
        int index = hashFunction(account->accountNumber);
        int originalIndex = index;

        while (table[index] != nullptr) {
            index = (index + 1) % tableSize;
            if (index == originalIndex) {
                cout << "Hash table is full. Cannot insert account." << endl;
                return;
            }
        }
        table[index] = account;
    }

    Account* search(int accountNumber) {
        int index = hashFunction(accountNumber);
        int originalIndex = index;

        while (table[index] != nullptr) {
            if (table[index]->accountNumber == accountNumber) {
                return table[index];
            }
            index = (index + 1) % tableSize;
            if (index == originalIndex) {
                break;
            }
        }
        return nullptr;
    }

    void remove(int accountNumber) {
        int index = hashFunction(accountNumber);
        int originalIndex = index;

        while (table[index] != nullptr) {
            if (table[index]->accountNumber == accountNumber) {
                delete table[index];
                table[index] = nullptr;
                cout << "Account removed successfully." << endl;
                return;
            }
            index = (index + 1) % tableSize;
            if (index == originalIndex) {
                break;
            }
        }
        cout << "Account not found." << endl;
    }

    ~HashTable() {
        for (int i = 0; i < tableSize; i++) {
            if (table[i] != nullptr) {
                delete table[i];
            }
        }
    }
};

void displayMenu() {
    cout << "\nBanking Management System\n";
    cout << "1. Create Account\n";
    cout << "2. Deposit\n";
    cout << "3. Withdraw\n";
    cout << "4. Check Balance\n";
    cout << "5. Remove Account\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    srand(time(0));

    HashTable bank(10);
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        if (choice == 1) {
            string holder;
            double initialBalance;

            cout << "Enter account holder's name: ";
            cin.ignore();
            getline(cin, holder);

            cout << "Enter initial balance: ";
            cin >> initialBalance;

            int accountNumber = rand() % 10000;
            Account* newAccount = new Account(holder, accountNumber, initialBalance);
            bank.insert(newAccount);

            cout << "Account created successfully with Account Number: " << accountNumber << endl;
        } 
        else if (choice == 2) {
            int accountNumber;
            double depositAmount;

            cout << "Enter account number: ";
            cin >> accountNumber;

            Account* account = bank.search(accountNumber);
            if (account) {
                cout << "Enter deposit amount: ";
                cin >> depositAmount;
                account->balance += depositAmount;
                cout << "Deposited " << depositAmount << ". New balance: " << account->balance << endl;
            } else {
                cout << "Account not found!" << endl;
            }
        } 
        else if (choice == 3) {
            int accountNumber;
            double withdrawAmount;

            cout << "Enter account number: ";
            cin >> accountNumber;

            Account* account = bank.search(accountNumber);
            if (account) {
                cout << "Enter withdrawal amount: ";
                cin >> withdrawAmount;

                if (withdrawAmount > account->balance) {
                    cout << "Insufficient balance!" << endl;
                } else {
                    account->balance -= withdrawAmount;
                    cout << "Withdrawn " << withdrawAmount << ". New balance: " << account->balance << endl;
                }
            } else {
                cout << "Account not found!" << endl;
            }
        } 
        else if (choice == 4) {
            int accountNumber;

            cout << "Enter account number: ";
            cin >> accountNumber;

            Account* account = bank.search(accountNumber);
            if (account) {
                cout << "Account Balance: " << account->balance << endl;
            } else {
                cout << "Account not found!" << endl;
            }
        } 
        else if (choice == 5) {
            int accountNumber;

            cout << "Enter account number to remove: ";
            cin >> accountNumber;

            bank.remove(accountNumber);
        } 
        else if (choice == 6) {
            cout << "Exiting the system. Goodbye!" << endl;
            break;
        } 
        else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
