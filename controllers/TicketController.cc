#include "TicketController.h"

void TicketController::getTickets(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) {
    LOG_DEBUG << "TicketController::getTickets";
    Json::Value ret;
    ret["result"] = "ok";
    auto resp = HttpResponse::newHttpJsonResponse(ret);
    callback(std::move(resp));
}

void TicketController::buyTickets(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) {}

void TicketController::refundTickets(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) {}

void TicketController::ticketInfo(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) {}