#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>

// Simple non-secure hash function
unsigned int simpleHash(const std::string& s) {
    unsigned int h = 0;
    for (char c : s) h = h * 31 + c;
    return h;
}

// Load users from file
std::unordered_map<std::string, unsigned int> loadUsers(const std::string& filename) {
    std::unordered_map<std::string, unsigned int> users;
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string user;
        unsigned int hash;
        if (iss >> user >> hash) {
            users[user] = hash;
        }
    }
    return users;
}

// Save users to file
void saveUsers(const std::unordered_map<std::string, unsigned int>& users, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& p : users) {
        file << p.first << " " << p.second << "\n";
    }
}

bool isValidUsername(const std::string& u) {
    if (u.size() < 3 || u.size() > 20) return false;
    for (char c : u) if (!isalnum(c)) return false;
    return true;
}

bool isValidPassword(const std::string& p) {
    return p.size() >= 6;
}

bool registerUser(std::unordered_map<std::string, unsigned int>& users, const std::string& username, const std::string& password) {
    if (!isValidUsername(username)) {
        std::cout << "Invalid username.\n";
        return false;
    }
    if (!isValidPassword(password)) {
        std::cout << "Password too short.\n";
        return false;
    }
    if (users.find(username) != users.end()) {
        std::cout << username << ", you are already registered.\n";
        return false;
    }
    users[username] = simpleHash(password);
    std::cout << "User '" << username << "' registered successfully.\n";
    return true;
}

bool loginUser(const std::unordered_map<std::string, unsigned int>& users, const std::string& username, const std::string& password) {
    auto it = users.find(username);
    if (it == users.end() || it->second != simpleHash(password)) {
        std::cout << "Username or password is incorrect.\n";
        return false;
    }
    std::cout << "Login successful. Welcome, " << username << "!\n";
    return true;
}

int main() {
    const std::string filename = "users.txt";
    auto users = loadUsers(filename);

    while (true) {
        std::cout << "\nChoose action: Register (r), Login (l), Quit (q): ";
        std::string action;
        std::getline(std::cin, action);

        if (action == "q") break;

        std::string username, password;
        std::cout << "Username: ";
        std::getline(std::cin, username);
        std::cout << "Password: ";
        std::getline(std::cin, password);

        if (action == "r") {
            if (registerUser(users, username, password)) {
                saveUsers(users, filename);
            }
        } else if (action == "l") {
            loginUser(users, username, password);
        } else {
            std::cout << "Invalid choice. Type 'r' to register, 'l' to login, or 'q' to quit.\n";
        }
    }

    return 0;
}
