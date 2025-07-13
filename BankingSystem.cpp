#include <iostream>
#include <unordered_map>
#include <deque>
#include <string>
#include <ctime>
#include <iomanip>

using std::string;
using std::cout;
using std::cin;
using std::unordered_map;
using std::deque;
using std::endl;
using std::fixed;
using std::setprecision;

//  Display welcome screen
void displayWelcomeScreen() {
    const int width = 80;
    auto center = [](const string& text, int width) {
        int pad = (width - static_cast<int>(text.length())) / 2;
        if (pad < 0) pad = 0;
        return string(pad, ' ') + text;
    };

    cout << "\n\n";
    cout << center("Welcome to MTNBank", width) << "\n\n";
    cout << center("Our Services:", width) << "\n";
    cout << center("- Buy Airtime and Electricity", width) << "\n";
    cout << center("- Transfer Money", width) << "\n";
    cout << center("- Deposit Money & Savings", width) << "\n";
    cout << center("- Stockvel Account Management", width) << "\n\n";
    cout << center("Please sign in to continue", width) << "\n";
    cout << center("Enter 1 to Login", width) << "\n";
    cout << center("Enter 2 to Register", width) << "\n";
    cout << center("Enter 3 to Quit", width) << "\n\n";
}

//  Transaction struct
struct Transaction {
    string type;
    double amount;
    time_t timestamp;

    Transaction(const string& t, double a) : type(t), amount(a), timestamp(time(0)) {}

    void display() const {
        cout << fixed << setprecision(2)
             << type << " of R" << amount << " at " << ctime(&timestamp);
    }
};

//  Account class
class Account {
private:
    string accountNumber;
    double balance;
    deque<Transaction> transactions;

public:
    Account(const string& accNum) : accountNumber(accNum), balance(0.0) {}

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount);
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds.\n";
            return false;
        }
        balance -= amount;
        transactions.emplace_back("Withdrawal", amount);
        return true;
    }

    bool transfer(Account& receiver, double amount) {
        if (withdraw(amount)) {
            receiver.deposit(amount);
            transactions.emplace_back("Transfer to " + receiver.getAccountNumber(), amount);
            return true;
        }
        return false;
    }

    const string& getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    void printTransactions() const {
        cout << "Transaction History [" << accountNumber << "]:\n";
        if (transactions.empty()) {
            cout << "No transactions yet.\n";
        } else {
            for (const auto& t : transactions)
                t.display();
        }
    }

    void showAccountInfo() const {
        cout << "\nAccount: " << accountNumber
             << "\nBalance: R" << fixed << setprecision(2) << balance << "\n";
        printTransactions();
    }
};

//  Customer class
class Customer {
private:
    string name;
    string id;
    string password;

public:
    unordered_map<string, Account> accounts;

    Customer() : name(""), id(""), password("") {}

    Customer(const string& n, const string& i, const string& p)
        : name(n), id(i), password(p) {}

    void createAccount(const string& accNum) {
        accounts.emplace(accNum, Account(accNum));
    }

    Account* getAccount(const string& accNum) {
        auto it = accounts.find(accNum);
        return (it != accounts.end()) ? &it->second : nullptr;
    }

    bool login(const string& enteredPass) const {
        return password == enteredPass;
    }

    const string& getName() const { return name; }
    const string& getID() const { return id; }
};

//  Main Program
int main() {
    unordered_map<string, Customer> users;
    users.emplace("0000001", Customer("Muzi Shange", "0000001", "muzi123"));
    users.emplace("0000002", Customer("John Doe", "0000002", "john456"));
    users["0000001"].createAccount("AC1001");
    users["0000002"].createAccount("AC1002");

    while (true) {
        displayWelcomeScreen();
        int action;
        cout << "Select Option (1 = Login, 2 = Register, 3 = Quit): ";
        cin >> action;

        if (action == 3) {
            cout << "Thank you for visiting MTNBank. Goodbye!\n";
            break;
        } else if (action == 2) {
            string name, id, pass, accNum;
            cout << "\n--- Register New User ---\n";
            cout << "Enter Full Name: ";
            cin.ignore();
            getline(cin, name);

            while (true) {
                cout << "Enter 7-digit ID: ";
                cin >> id;

                if (id.length() != 7) {
                    cout << "ID must be exactly 7 digits.\n";
                } else if (users.find(id) != users.end()) {
                    cout << "⚠️  ID already exists. Please enter a different 7-digit ID.\n";
                } else {
                    break;
                }
            }

            cout << "Enter Password: ";
            cin >> pass;
            cout << "Create Account Number (e.g. AC1003): ";
            cin >> accNum;

            users.emplace(id, Customer(name, id, pass));
            users[id].createAccount(accNum);
            cout << " Registered Successfully! You can now log in.\n\n";
            continue;
        } else if (action != 1) {
            cout << " Invalid option. Try again.\n";
            continue;
        }

        string enteredID, enteredPass, enteredAccNum;
        cout << "\n--- Login ---\n";
        cout << "Enter 7-digit User ID: ";
        cin >> enteredID;
        if (enteredID.length() != 7) {
            cout << "ID must be exactly 7 digits.\n";
            continue;
        }
        cout << "Enter Password: ";
        cin >> enteredPass;

        auto it = users.find(enteredID);
        if (it == users.end() || !it->second.login(enteredPass)) {
            cout << "\n Incorrect ID or Password. Try again.\n\n";
            continue;
        }

        Customer& currentUser = it->second;
        cout << "Enter Account Number: ";
        cin >> enteredAccNum;
        Account* userAcc = currentUser.getAccount(enteredAccNum);

        if (!userAcc) {
            cout << " Account not found.\n";
            continue;
        }

        int choice;
        cout << "\nWelcome, " << currentUser.getName() << "!\n";
        cout << "Current Balance: R" << fixed << setprecision(2) << userAcc->getBalance() << "\n";
        cout << "Choose a service:\n";
        cout << "1. Deposit Money\n";
        cout << "2. Withdraw Money\n";
        cout << "3. View Account Info\n";
        cout << "4. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        if (choice == 1) {
            double amount;
            cout << "Enter deposit amount: R";
            cin >> amount;
            userAcc->deposit(amount);
            cout << "Updated Balance: R" << fixed << setprecision(2) << userAcc->getBalance() << "\n";
        } else if (choice == 2) {
            double amount;
            cout << "Enter withdrawal amount: R";
            cin >> amount;
            if (userAcc->withdraw(amount)) {
                cout << "Updated Balance: R" << fixed << setprecision(2) << userAcc->getBalance() << "\n";
            }
        } else if (choice == 3) {
            userAcc->showAccountInfo();
        } else {
            cout << "Exiting service menu...\n";
            continue;
        }

        int next;
        cout << "\nPress 0 to reset or 1 to continue: ";
        cin >> next;
        cin.clear();                  //  clear error state if any
        cin.ignore(1000, '\n');       //  discard leftover input

        if (next == 0) {
            cout << "\nSession reset...\n\n";
            continue;
        } else {
            cout << "\nThank you for using MTNBank. Goodbye!\n";
            break;
        }
    }

    return 0;
}
