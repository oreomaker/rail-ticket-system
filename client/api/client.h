#pragma once

#include "httplib/httplib.h"
#include <iostream>

namespace rail_ticket {
class Client {
private:
    httplib::Client cli;
    std::string token;

public:
    Client() : cli("localhost"){};
    ~Client(){};
    // user
    std::pair<int, std::string> login(std::string username, std::string password);
    // train
};
} // namespace rail_ticket
