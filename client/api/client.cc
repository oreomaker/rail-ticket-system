#include "client.h"
#include <json/reader.h>
#include <json/value.h>
#include <string>
#include <utility>

std::pair<int, std::string> rail_ticket::Client::login(std::string username, std::string password) {
    Json::Value param;
    param["username"] = username;
    param["password"] = password;

    auto result =
        cli.Post("/user/login", param.toStyledString(), "application/json");

    Json::Reader reader;
    Json::Value res;
    reader.parse(result->body, res);

    if (res["code"] == 0) {
        this->token = res["token"].asString();
        return std::pair<int, std::string> (res["code"].asInt(), res["token"].asString());
    } else {
        return std::pair<int, std::string> (res["code"].asInt(), res["message"].asString());
    }
}