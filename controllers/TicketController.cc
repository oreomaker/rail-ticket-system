#include "TicketController.h"
#include <bitset>
#include <drogon/orm/Mapper.h>
#include <fmt/format.h>
#include <string>

void TicketController::insertTickets(const std::vector<Train> &trains) {
    auto dbTranc = drogon::app().getDbClient()->newTransaction();
    std::vector<char> seatPosition = {'A', 'B', 'C', 'D', 'E'};
    for (auto &train : trains) { // 遍历所有列车
        // 每一个列车进行一次插入
        std::string sql =
            "insert into ticket (trip, seatType, carriage, seatPosition, "
            "available, startStation, endStation) values ";

        int carriage = *train.getCarriage();
        int stationNum = *train.getStationnum();
        std::string trip = *train.getTrip();
        std::bitset<16> startStation,
            endStation; // 16个站点, 0表示不经过, 1表示经过, 从低位到高位
        startStation[0] = 1;
        endStation[stationNum - 1] = 1;
        for (int i = 0; i < carriage; ++i) { // 遍历所有车厢
            int seatType;
            if (i > 2) { // 二等座
                seatType = 2;
            } else if (i == 1) { // 一等座
                seatType = 1;
            } else if (i == 0) { // 商务座
                seatType = 0;
            }
            for (char seatPos : seatPosition) { // 遍历所有座位位置
                sql += fmt::format("('{}',{},{},'{}',{},'{}','{}'),", trip,
                                   seatType, i, seatPos, stationNum,
                                   startStation.to_string(),
                                   endStation.to_string());
            }
        }
        sql.pop_back();
        dbTranc->execSqlSync(sql);
    }
}

void TicketController::generateTickets(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) {

    LOG_DEBUG << "TicketController::generateTickets";
    // 暂时采用清空数据库的方式
    auto clientPtr = drogon::app().getDbClient();
    std::string sql = "delete from ticket";
    try {
        clientPtr->execSqlSync(sql);
    } catch (const orm::DrogonDbException &e) {
        LOG_ERROR << e.base().what();
        Json::Value ret;
        ret["code"] = 1;
        ret["msg"] = "数据库错误";
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        callback(std::move(resp));
    }

    // 生成车票
    orm::Mapper<Train> trainMapper(clientPtr);
    orm::Mapper<Ticket> ticketMapper(clientPtr);
    auto trainList = trainMapper.findAll();

    this->insertTickets(trainList);

    Json::Value ret;
    ret["code"] = 0;
    auto resp = HttpResponse::newHttpJsonResponse(ret);
    callback(std::move(resp));
}

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