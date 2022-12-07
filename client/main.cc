#include "api/client.h"
#include <iostream>

rail_ticket::Client cli;

void printGreeting() {
    std::cout << "========================================" << std::endl;
    std::cout << "Welcome to the Rail Ticket System Client" << std::endl;
    std::cout << "========================================" << std::endl
              << std::endl;
}

void printPrompt() { std::cout << "Please enter your command: " << std::endl; }

void printHelp() {
    std::cout << "Available commands:" << std::endl;
    std::cout << "  help: print this help message" << std::endl;
    std::cout << "  query: query ticket" << std::endl;
    std::cout << "  line: query train line info" << std::endl;
    std::cout << "  buy: buy ticket" << std::endl;
    std::cout << "  query_order: query order" << std::endl;
    std::cout << "  refund: refund ticket" << std::endl;
    std::cout << "  exit: exit the system" << std::endl;
}

void query() {
    std::string start, end, date;
    std::cout << "Please enter the start station: " << std::endl;
    std::cin >> start;
    std::cout << "Please enter the end station: " << std::endl;
    std::cin >> end;
    auto resultDirect = cli.queryDirect(start, end);
    if (resultDirect.first == 0) {
        std::cout << "Query successfully" << std::endl << std::endl;
        std::cout << "# Direct Trip:" << std::endl;
        for (auto &trip : resultDirect.second) {
            std::cout << "Train ID: " << trip["trip"].asString() << std::endl;
            std::cout << "Start Station: " << trip["startStation"].asString()
                      << std::endl;
            std::cout << "End Station: " << trip["endStation"].asString()
                      << std::endl;
            std::cout << "Start Time: " << trip["startTime"].asString()
                      << std::endl;
            std::cout << "End Time: " << trip["endTime"].asString()
                      << std::endl;
            std::cout << "Duration: " << trip["duration"].asString()
                      << std::endl;
            std::cout << "Carriage: " << trip["carriage"].asString()
                      << std::endl;
            std::cout << "Train Type: " << trip["type"].asString() << std::endl;
            std::cout << "-------------------" << std::endl;
        }
    }

    auto resultTransfer = cli.queryTransfer(start, end);
    if (resultDirect.first == 0) {
        std::cout << "# Transfer Trip:" << std::endl;
        for (auto &trip : resultTransfer.second) {
            std::cout << "------ Trip 1 ------"
                      << "\t------ Trip 2 ------" << std::endl;
            std::cout << "Train ID: " << trip["trip1"]["trip"].asString()
                      << "\t\tTrain ID: " << trip["trip2"]["trip"].asString()
                      << std::endl;
            std::cout << "Start Station: "
                      << trip["trip1"]["startStation"].asString()
                      << "\tStart Station: "
                      << trip["trip2"]["startStation"].asString() << std::endl;
            std::cout << "End Station: "
                      << trip["trip1"]["endStation"].asString()
                      << "\tEnd Station: "
                      << trip["trip2"]["endStation"].asString() << std::endl;
            std::cout << "Start Time: " << trip["trip1"]["startTime"].asString()
                      << "\tStart Time: " << trip["trip2"]["startTime"].asString()
                      << std::endl;
            std::cout << "End Time: " << trip["trip1"]["endTime"].asString()
                      << "\tEnd Time: " << trip["trip2"]["endTime"].asString()
                      << std::endl;
            std::cout << "Duration: " << trip["trip1"]["duration"].asString()
                      << "\tDuration: " << trip["trip2"]["duration"].asString()
                      << std::endl;
            std::cout << "Carriage: " << trip["trip1"]["carriage"].asString()
                      << "\t\tCarriage: " << trip["trip2"]["carriage"].asString()
                      << std::endl;
            std::cout << "Train Type: " << trip["trip1"]["type"].asString()
                      << "\tTrain Type: " << trip["trip2"]["type"].asString()
                      << std::endl;
            std::cout << "------------------ Inter  ------------------" << std::endl;
            std::cout << "Inter Station: " << trip["interStation"].asString()
                      << std::endl;
            std::cout << "Inter Arrive Time: "
                      << trip["interArriveTime"].asString() << std::endl;
            std::cout << "Inter Leaving Time: "
                      << trip["interLeavingTime"].asString() << std::endl;
            std::cout << "--------------------------------------------" << std::endl;
        }
    }
}

void query_line(){
    
}

void buy() {
    std::string train_id, date, start, end, seat_type;
    std::cout << "Please enter the train id: " << std::endl;
    std::cin >> train_id;
    std::cout << "Please enter the date: " << std::endl;
    std::cin >> date;
    std::cout << "Please enter the start station: " << std::endl;
    std::cin >> start;
    std::cout << "Please enter the end station: " << std::endl;
    std::cin >> end;
    std::cout << "Please enter the seat type: " << std::endl;
    std::cin >> seat_type;
    // auto result = cli.buyTicket(train_id, date, start, end, seat_type);
    // if (result.first == 0) {
    //     std::cout << "Buy successfully" << std::endl;
    //     std::cout << result.second << std::endl;
    // } else {
    //     std::cout << result.second << std::endl;
    // }
}

void query_order() {
    // auto result = cli.queryOrder();
    // if (result.first == 0) {
    //     std::cout << "Query successfully" << std::endl;
    //     std::cout << result.second << std::endl;
    // } else {
    //     std::cout << result.second << std::endl;
    // }
}

void refund() {
    std::string order_id;
    std::cout << "Please enter the order id: " << std::endl;
    std::cin >> order_id;
    // auto result = cli.refundTicket(order_id);
    // if (result.first == 0) {
    //     std::cout << "Refund successfully" << std::endl;
    //     std::cout << result.second << std::endl;
    // } else {
    //     std::cout << result.second << std::endl;
    // }
}

int main() {
    std::string username, password, command;

    printGreeting();

    while (true) {
        std::cout << "Please enter your username: " << std::endl;
        std::cin >> username;
        std::cout << "Please enter your password: " << std::endl;
        std::cin >> password;

        auto result = cli.login(username, password);

        if (result.first == 0) {
            std::cout << "Successfully log in" << std::endl;
            std::cout << "========================================"
                      << std::endl;
            break;
        } else {
            std::cout << result.second << std::endl;
        }
    }

    printHelp();
    while (true) {
        std::cout << ">Input the command:" << std::endl;
        std::cin >> command;
        if (command == "help") {
            printHelp();
        } else if (command == "query") {
            query();
        } else if(command == "line"){
            query_line();
        } else if (command == "buy") {
            buy();
        } else if (command == "query_order") {
            query_order();
        } else if (command == "refund") {
            refund();
        } else if (command == "exit") {
            std::cout << "Bye" << std::endl;
            break;
        } else {
            std::cout << "Invalid command" << std::endl;
        }
    }

    return 0;
}