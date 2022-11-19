#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class TicketController : public drogon::HttpController<TicketController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(TicketController::getTickets,
                  "/absolute/path/{1}/{2}/list", Get);

    METHOD_LIST_END

    void getTickets(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback,
                    int p1, std::string p2);
    void buyTickets(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback,
                    int p1, std::string p2);
};
