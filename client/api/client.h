#pragma once

#include <httplib.h>
#include <iostream>
#include <json/reader.h>
#include <json/value.h>

namespace rail_ticket {
class Client {
private:
    httplib::Client cli;
    std::string token;
    std::vector<int> order_ids;

public:
    Client() : cli("localhost"){};
    ~Client(){};
    // user
    std::pair<int, std::string> login(std::string username,
                                      std::string password);
    // train
    std::pair<int, Json::Value> queryDirect(std::string start, std::string end);
    std::pair<int, Json::Value> queryTransfer(std::string start,
                                              std::string end);
    // ticket
    std::pair<int, Json::Value> buyTicket(std::string trip, std::string start,
                                          std::string end, int type);
    std::pair<int, Json::Value> queryOrder();
    std::pair<int, Json::Value> refundTicket(int id);
};
} // namespace rail_ticket
