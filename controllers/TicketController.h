#pragma once

#include "models/Line.h"
#include "models/Ticket.h"
#include "models/Train.h"
#include <bitset>
#include <drogon/HttpController.h>

using namespace drogon;
using namespace drogon_model::rail_ticket;

class TicketController : public drogon::HttpController<TicketController> {
private:
    // 根据列车生成全部车票插入数据库
    void insertTickets(const std::vector<Train> &tickets);
    std::bitset<16> gnerateStationFlag(int start, int end);
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(TicketController::generateTickets, "/ticket/generate", Post,
                  "LoginFilter", "AdminFilter");
    ADD_METHOD_TO(TicketController::getTickets,
                  "/ticket?trip={1}&start={2}&end={3}&type={4}", Get, "LineFilter");
    ADD_METHOD_TO(TicketController::buyTickets, "/ticket/buy", Post);
    ADD_METHOD_TO(TicketController::refundTickets, "/ticket/refund", Post);
    ADD_METHOD_TO(TicketController::ticketInfo, "/ticket/info?id={1}", Get);
    METHOD_LIST_END

    void
    generateTickets(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback);
    void getTickets(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback,
                    const std::string &trip, const std::string &start,
                    const std::string &end, const char &type);
    void buyTickets(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback);
    void refundTickets(const HttpRequestPtr &req,
                       std::function<void(const HttpResponsePtr &)> &&callback);
    void ticketInfo(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback, const std::string &id);
};
