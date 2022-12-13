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

std::pair<int, Json::Value> rail_ticket::Client::buyTicket(std::string trip,
                                                           std::string start,
                                                           std::string end,
                                                           int type) {
    httplib::Headers headers;
    headers.insert(std::make_pair("Authorization", this->token));
    cli.set_default_headers(headers);

    Json::Value param;
    param["trip"] = trip;
    param["start"] = start;
    param["end"] = end;
    param["type"] = type;

    auto result =
        cli.Post("/ticket/buy", param.toStyledString(), "application/json");

    Json::Reader reader;
    Json::Value res;
    reader.parse(result->body, res);

    if (res["code"].asInt() == 0) {
        return std::pair<int, Json::Value>(res["code"].asInt(), res["data"]);
    } else {
        return std::pair<int, Json::Value>(res["code"].asInt(), res["msg"]);
    }
}

std::pair<int, Json::Value> rail_ticket::Client::queryOrder() {
    httplib::Headers headers;
    headers.insert(std::make_pair("Authorization", this->token));
    cli.set_default_headers(headers);

    auto result = cli.Get("/ticket/orders");

    Json::Reader reader;
    Json::Value res;
    reader.parse(result->body, res);

    if (res["code"].asInt() == 0) {
        this->order_ids.erase(order_ids.begin(), order_ids.end());
        std::cout << order_ids.size() << std::endl;
        for (auto &item : res["data"]) {
            this->order_ids.push_back(item["id"].asInt());
        }
    }

    return std::pair<int, Json::Value>(res["code"].asInt(), res["data"]);
}

std::pair<int, Json::Value> rail_ticket::Client::refundTicket(int order_id) {
    httplib::Headers headers;
    headers.insert(std::make_pair("Authorization", this->token));
    cli.set_default_headers(headers);

    if (order_id > this->order_ids.size() || order_id < 1) {
        return std::pair<int, Json::Value>(-1, "id out of range");
    }

    auto result = cli.Post("/ticket/refund?id=" +
                           std::to_string(this->order_ids[order_id - 1]));

    Json::Reader reader;
    Json::Value res;
    reader.parse(result->body, res);

    return std::pair<int, Json::Value>(res["code"].asInt(), res["data"]);
}