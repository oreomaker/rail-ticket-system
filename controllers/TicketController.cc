#include "TicketController.h"

void TicketController::getTickets(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback, int p1,
    std::string p2) {
    LOG_DEBUG << "TicketController::getTickets";
    Json::Value ret;
    ret["result"] = "ok";
    ret["p1"] = p1;
    ret["p2"] = p2;
    auto resp = HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}