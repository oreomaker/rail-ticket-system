#pragma once

#include "models/Line.h"
#include "models/Ticket.h"
#include "models/TicketOrder.h"
#include "models/Train.h"
#include <bitset>
#include <drogon/HttpController.h>

using namespace drogon;
using namespace drogon_model::rail_ticket;

struct OrderRequest { // 用于接收购票请求
    std::string trip;
    std::string start;
    std::string end;
    int type;
};

namespace drogon {
template <> inline OrderRequest fromRequest(const HttpRequest &req) {
    auto json = req.getJsonObject();
    OrderRequest order;
    if (json) {
        order.trip = (*json)["trip"].asString();
        order.start = (*json)["start"].asString();
        order.end = (*json)["end"].asString();
        order.type = (*json)["type"].asInt();
    }
    return order;
}

} // namespace drogon

class TicketController : public drogon::HttpController<TicketController> {
private:
    // 根据列车生成全部车票插入数据库
    void insertTickets(const std::vector<Train> &tickets);
    // 生成站线标志
    inline std::bitset<16> gnerateStationFlag(int start, int end);
    // 二进制数字转16进制字符串
    inline std::string numTo16Hex(unsigned long);
    // 生成车票价格
    std::string calculateAmount(float startMile, float endMile, int type);

public:
    METHOD_LIST_BEGIN
    // 生成车票
    ADD_METHOD_TO(TicketController::generateTickets, "/ticket/generate", Post,
                  "LoginFilter", "AdminFilter");
    // 查询车票
    ADD_METHOD_TO(TicketController::getTickets,
                  "/ticket?trip={1}&start={2}&end={3}&type={4}", Get,
                  "LineFilter");
    // 购票
    ADD_METHOD_TO(TicketController::buyTickets, "/ticket/buy", Post,
                  "LoginFilter", "LineFilter");
    // 查询订单
    ADD_METHOD_TO(TicketController::queryOrder, "/ticket/orders", Get,
                  "LoginFilter");
    // 退票
    ADD_METHOD_TO(TicketController::refundTickets, "/ticket/refund?id={1}", Post,
                  "LoginFilter");
    // 根据id查询车票信息
    ADD_METHOD_TO(TicketController::ticketInfo, "/ticket/info?id={1}", Get,
                  "LoginFilter");
    METHOD_LIST_END

    void
    generateTickets(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback);
    void getTickets(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback,
                    const std::string &trip, const std::string &start,
                    const std::string &end, int type);
    void buyTickets(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback,
                    OrderRequest &&order);
    void queryOrder(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback);
    void refundTickets(const HttpRequestPtr &req,
                       std::function<void(const HttpResponsePtr &)> &&callback,
                       int id);
    void ticketInfo(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback,
                    const std::string &id);
};
