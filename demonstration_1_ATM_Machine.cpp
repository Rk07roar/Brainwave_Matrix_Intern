#include <iostream>
#include <vector>
#include <string>
#include <ctime>


using namespace std;

class Transaction {
public:
    string type;
    double amount;
    string date;
    Transaction(string t, double a, string d) : type(t), amount(a), date(d) {}
};

class ATM {
    string pin = "1234";
    double balance = 1000.0;
    vector<Transaction> history;

public:
    string username;
    
    bool authenticate(string enteredPin) {
        return enteredPin == pin;
    }

    void displayMenu() {
        cout << "\nATM Menu:\n";
        cout << "1. Check Balance\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer\n";
        cout << "5. Change PIN\n";
        cout << "6. View Transaction History\n";
        cout << "7. Exit\n";
    }

    void checkBalance() {
        cout << "Current Balance: $" << balance << endl;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            recordTransaction("Deposit", amount);
            cout << "$" << amount << " deposited successfully.\n";
        } else {
            cout << "Invalid deposit amount.\n";
        }
    }

    void withdraw(double amount) {
        if (amount <= balance && amount > 0) {
            balance -= amount;
            recordTransaction("Withdraw", amount);
            cout << "$" << amount << " withdrawn successfully.\n";
        } else if (amount > balance) {
            cout << "Insufficient balance.\n";
        } else {
            cout << "Invalid withdrawal amount.\n";
        }
    }

    void transfer(double amount, string recipient) {
        if (amount <= balance && amount > 0) {
            balance -= amount;
            recordTransaction("Transfer to " + recipient, amount);
            cout << "$" << amount << " transferred to " << recipient << " successfully.\n";
        } else if (amount > balance) {
            cout << "Insufficient balance.\n";
        } else {
            cout << "Invalid transfer amount.\n";
        }
    }

    void changePin(string newPin) {
        pin = newPin;
        cout << "PIN changed successfully.\n";
    }

    void recordTransaction(string type, double amount) {
        time_t now = time(0);
        char* dt = ctime(&now);
        history.push_back(Transaction(type, amount, dt));
    }

    void viewHistory() {
        cout << "\nTransaction History:\n";
        if (history.empty()) {
            cout << "No transactions yet.\n";
        } else {
            for (auto &trans : history) {
                cout << trans.date << " - " << trans.type << ": $" << trans.amount << endl;
            }
        }
    }

    void printMenuAndProcess() {
        int choice;
        double amount;
        string recipient, newPin;
        while (true) {
            displayMenu();
            cout << "Choose an option: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    checkBalance();
                    break;
                case 2:
                    cout << "Enter amount to deposit: $";
                    cin >> amount;
                    deposit(amount);
                    break;
                case 3:
                    cout << "Enter amount to withdraw: $";
                    cin >> amount;
                    withdraw(amount);
                    break;
                case 4:
                    cout << "Enter recipient username: ";
                    cin >> recipient;
                    cout << "Enter amount to transfer: $";
                    cin >> amount;
                    transfer(amount, recipient);
                    break;
                case 5:
                    cout << "Enter new PIN: ";
                    cin >> newPin;
                    changePin(newPin);
                    break;
                case 6:
                    viewHistory();
                    break;
                case 7:
                    cout << "Exiting... Thank you for using our ATM.\n";
                    return;
                default:
                    cout << "Invalid option. Try again.\n";
            }
        }
    }
};

class User {
public:
    string username;
    string pin;
    ATM atm;

    User(string user, string p) : username(user), pin(p) {}

    bool authenticate(string enteredPin) {
        return enteredPin == pin;
    }
};

int main() {
    vector<User> users;
    users.push_back(User("Roshan", "1234"));
    users.push_back(User("user2", "4321"));

    string username, pin;
    bool authenticated = false;
    User* loggedInUser = nullptr;

    cout << "Enter username: ";
    cin >> username;

    for (auto &user : users) {
        if (user.username == username) {
            loggedInUser = &user;
            break;
        }
    }

    if (loggedInUser == nullptr) {
        cout << "Invalid username.\n";
        return 0;
    }

    int attempts = 3;
    while (attempts > 0) {
        cout << "Enter PIN: ";
        cin >> pin;
        if (loggedInUser->authenticate(pin)) {
            authenticated = true;
            break;
        } else {
            attempts--;
            cout << "Invalid PIN. You have " << attempts << " attempts left.\n";
        }
    }

    if (!authenticated) {
        cout << "Authentication failed. Access denied.\n";
        return 0;
    }

    cout << "Welcome " << loggedInUser->username << "!\n";
    loggedInUser->atm.printMenuAndProcess();

    return 0;
}
















