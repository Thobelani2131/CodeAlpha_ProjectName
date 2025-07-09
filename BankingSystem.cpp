#include <iostream>
#include <unordered_map>
#include <deque>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

// ✅ Transaction struct
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

// ✅ Account class
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
        for (const auto& t : transactions)
            t.display();
    }

    void showAccountInfo() const {
        cout << "\nAccount: " << accountNumber
             << "\nBalance: R" << fixed << setprecision(2) << balance << "\n";
        printTransactions();
    }
};

// ✅ Customer class
class Customer {
private:
    string name;
    string id;

public:
    unordered_map<string, Account> accounts;

    Customer(const string& n, const string& i) : name(n), id(i) {}

    void createAccount(const string& accNum) {
        accounts.emplace(accNum, Account(accNum));
    }

    Account* getAccount(const string& accNum) {
        auto it = accounts.find(accNum);
        return (it != accounts.end()) ? &it->second : nullptr;
    }

    const string& getName() const { return name; }
    const string& getID() const { return id; }
};

// ✅ Main
int main() {
    Customer muzi("Muzi Shange", "001");
    Customer john("John Doe", "002");

    muzi.createAccount("AC1001");
    john.createAccount("AC1002");

    Account* muziAcc = muzi.getAccount("AC1001");
    Account* johnAcc = john.getAccount("AC1002");

    if (muziAcc && johnAcc) {
        muziAcc->deposit(1000);
        muziAcc->withdraw(200);
        muziAcc->transfer(*johnAcc, 300);
    }

    cout << "\n--- MUZI ACCOUNT INFO ---\n";
    muziAcc->showAccountInfo();

    cout << "\n--- JOHN ACCOUNT INFO ---\n";
    johnAcc->showAccountInfo();

    return 0;
}
