#include <iostream>

void printGreeting(){
    std::cout << "==============================" << std::endl;
    std::cout << "Welcome to the Rail Ticket System Client" << std::endl;
    std::cout << "==============================" << std::endl;
}

void printPrompt(){
    std::cout << "Please enter your command: " << std::endl;
}

int main() {
    printGreeting();
    std::string input;
    while(true){
        printPrompt();
        std::cin >> input;
        std::cout << input << std::endl;
    }
    return 0;
}