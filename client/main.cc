// #include "api/login.h"
#include <iostream>

void printGreeting() {
    std::cout << "==============================" << std::endl;
    std::cout << "Welcome to the Rail Ticket System Client" << std::endl;
    std::cout << "==============================" << std::endl;
}

void printPrompt() { std::cout << "Please enter your command: " << std::endl; }

int main() {
    printGreeting();
    std::string input, username, password;
    // LoginClient l;

    while (true) {
        std::cout << "Please enter your username: " << std::endl;
        std::cin >> username;
        std::cout << "Please enter your password: " << std::endl;
        std::cin >> password;
        // l.login(username, password);
    }
    return 0;
}