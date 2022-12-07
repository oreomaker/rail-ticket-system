#include "client.h"
#include <string>
#include <utility>

std::pair<int, std::string> rail_ticket::Client::login(std::string username,
                                                       std::string password) {
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
        return std::pair<int, std::string>(res["code"].asInt(),
                                           res["token"].asString());
    } else {
        return std::pair<int, std::string>(res["code"].asInt(),
                                           res["message"].asString());
    }
}

std::pair<int, Json::Value> rail_ticket::Client::queryDirect(std::string start,
                                                             std::string end) {
    auto result = cli.Get("/train?start=" + start + "&end=" + end);

    Json::Reader reader;
    Json::Value res;
    reader.parse(result->body, res);

    auto data = res["data"];

    return std::pair<int, Json::Value>(res["code"].asInt(), res["data"]);
}

std::pair<int, Json::Value>
rail_ticket::Client::queryTransfer(std::string start, std::string end) {
    auto result = cli.Get("/train-transfer?start=" + start + "&end=" + end);

    Json::Reader reader;
    Json::Value res;
    reader.parse(result->body, res);

    return std::pair<int, Json::Value>(res["code"].asInt(), res["data"]);
}