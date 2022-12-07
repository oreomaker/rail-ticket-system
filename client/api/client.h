#pragma once

#include "httplib/httplib.h"
#include <iostream>
#include <json/reader.h>
#include <json/value.h>

namespace rail_ticket {
class Client {
private:
    httplib::Client cli;
    std::string token;

public:
    Client() : cli("localhost"){};
    ~Client(){};
    // user
    std::pair<int, std::string> login(std::string username,
                                      std::string password);
    // train
    std::pair<int, Json::Value> queryDirect(std::string start, std::string end);
    std::pair<int, Json::Value> queryTransfer(std::string start, std::string end);
};
} // namespace rail_ticket
