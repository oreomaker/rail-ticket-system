#include "TicketController.h"
#include <drogon/orm/Mapper.h>
#include <fmt/format.h>
#include <json/value.h>

void TicketController::insertTickets(const std::vector<Train> &trains) {
    auto dbTranc = drogon::app().getDbClient()->newTransaction();
    std::vector<char> seatPosition = {'A', 'B', 'C', 'D', 'E'};
    for (auto &train : trains) { // 遍历所有列车
        // 每一个列车进行一次插入
        std::string sql =
            "insert into ticket (trip, seatType, carriage, seatPosition, "
            "available, startConstraint, endConstraint, stationFlag) values ";

        int carriage = *train.getCarriage();
        int stationNum = *train.getStationnum();
        std::string trip = *train.getTrip();

        // 16个站点, 0表示不经过, 1表示经过, 从低位到高位
        // startConstraint如0000000000000001，控制始发站
        // endConstraint如1000000000000000，控制终点站
        // stationFlag为经过的站点
        std::bitset<16> startConstraint, endConstraint, stationFlag;
        startConstraint[0] = 1;
        stationFlag[0] = 1;
        endConstraint[stationNum - 1] = 1;
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
                sql += fmt::format(
                    "('{}',{},{},'{}',{},'{}','{}','{}'),", trip, seatType, i,
                    seatPos, stationNum, startConstraint.to_string(),
                    endConstraint.to_string(), stationFlag.to_string());
            }
        }
        sql.pop_back();
        dbTranc->execSqlSync(sql);
    }
}

std::bitset<16> TicketController::gnerateStationFlag(int start, int end) {
    std::bitset<16> stationFlag;
    for (int i = start; i <= end; ++i) {
        stationFlag[i] = 1;
    }
    return stationFlag;
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
        ret["msg"] = "Database fault";
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
    std::function<void(const HttpResponsePtr &)> &&callback,
    const std::string &trip, const std::string &start, const std::string &end,
    const char &type) {

    LOG_DEBUG << "TicketController::getTickets";
    // 查找线路信息
    auto clientPtr = drogon::app().getDbClient();

    orm::Mapper<Line> trainMapper(clientPtr);
    // 异常已在filter处理
    Line lineStart = trainMapper.findOne(
        orm::Criteria(Line::Cols::_trip, orm::CompareOperator::EQ, trip) &&
        orm::Criteria(Line::Cols::_trip, orm::CompareOperator::EQ, start));
    Line lineEnd = trainMapper.findOne(
        orm::Criteria(Line::Cols::_trip, orm::CompareOperator::EQ, trip) &&
        orm::Criteria(Line::Cols::_trip, orm::CompareOperator::EQ, end));

    // 查找车票信息
    auto stationFlag = this->gnerateStationFlag(*lineStart.getPosition(),
                                                *lineEnd.getPosition());
    // 查找符合乘车区间并且按照余票数最大给出结果
    std::string sql =
        fmt::format("select * from ticket where trip={} and type={} "
                    "and stationFlag=~((~stationFlag)|'{}') "
                    "order by available asc , carriage asc",
                    trip, type, stationFlag.to_string());
    auto ticketList = clientPtr->execSqlSync(sql);

    Json::Value ret;
    ret["code"] = 0;
    if (ticketList.empty()) {
        ret["data"] = Json::arrayValue;
    } else {
        for (auto &ticket : ticketList) {
            ret["data"].append(ticket["id"].as<std::string>());
        }
        ret["count"] = (int)ticketList.size();
    }
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
    std::function<void(const HttpResponsePtr &)> &&callback,
    const std::string &end) {}