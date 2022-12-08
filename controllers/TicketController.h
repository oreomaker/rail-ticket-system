#pragma once

#include "models/Train.h"
#include "models/Ticket.h"
#include <drogon/HttpController.h>

using namespace drogon;
using namespace drogon_model::rail_ticket;

class TicketController : public drogon::HttpController<TicketController> {
private:
    void insertTickets(const std::vector<Train> &tickets);
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(TicketController::generateTickets, "/ticket/generate", Post,
                  "LoginFilter", "AdminFilter");
    ADD_METHOD_TO(TicketController::getTickets, "/ticket", Get);
    ADD_METHOD_TO(TicketController::buyTickets, "/ticket/buy", Post);
    ADD_METHOD_TO(TicketController::refundTickets, "/ticket/refund", Post);
    ADD_METHOD_TO(TicketController::ticketInfo, "/ticket/info", Get);
    METHOD_LIST_END

    void
    generateTickets(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback);
    void getTickets(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback);
    void buyTickets(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback);
    void refundTickets(const HttpRequestPtr &req,
                       std::function<void(const HttpResponsePtr &)> &&callback);
    void ticketInfo(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback);
};
