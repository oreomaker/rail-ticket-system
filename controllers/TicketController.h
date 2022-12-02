#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class TicketController : public drogon::HttpController<TicketController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(TicketController::getTickets, "/ticket", Get);
    ADD_METHOD_TO(TicketController::buyTickets, "/ticket/buy", Post);
    ADD_METHOD_TO(TicketController::refundTickets, "/ticket/refund", Post);
    ADD_METHOD_TO(TicketController::ticketInfo, "/ticket/info", Get);
    METHOD_LIST_END

    void getTickets(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback);
    void buyTickets(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback);
    void refundTickets(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback); 
    void ticketInfo(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback); 
};
