#include "api/client.h"
#include <iostream>

void printGreeting() {
    std::cout << "========================================" << std::endl;
    std::cout << "Welcome to the Rail Ticket System Client" << std::endl;
    std::cout << "========================================" << std::endl
              << std::endl;
}

void printPrompt() { std::cout << "Please enter your command: " << std::endl; }

int main() {
    printGreeting();
    std::string username, password;
    rail_ticket::Client cli;

    while (true) {
        std::cout << "Please enter your username: " << std::endl;
        std::cin >> username;
        std::cout << "Please enter your password: " << std::endl;
        std::cin >> password;

        auto result = cli.login(username, password);

        if (result.first == 0) {
            std::cout << "Successfully log in" << std::endl;
            break;
        } else {
            std::cout << result.second << std::endl;
        }
    }

    return 0;
}