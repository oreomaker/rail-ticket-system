#include "TicketController.h"
#include "TicketOrder.h"
#include "plugins/UserInfo.h"
#include <drogon/orm/Exception.h>
#include <drogon/orm/Mapper.h>
#include <exception>
#include <fmt/format.h>
#include <json/value.h>
#include <string>
#include <trantor/utils/Logger.h>

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
                    "('{}',{},{},'{}',{},{},{},{}),", trip, seatType, i,
                    seatPos, stationNum, startConstraint.to_ulong(),
                    endConstraint.to_ulong(), stationFlag.to_ulong());
            }
        }
        sql.pop_back();
        dbTranc->execSqlSync(sql);
    }
}

std::bitset<16> TicketController::gnerateStationFlag(int start, int end) {
    std::bitset<16> stationFlag;
    for (int i = start; i < end; ++i) {
        stationFlag[i] = 1;
    }
    return stationFlag;
}

std::string TicketController::numTo16Hex(unsigned long num) {
    unsigned long x;
    std::string s("0x0000");
    char c;
    for (int i = 1; i <= 4 && x != 0; ++i) {
        x = num % 16;
        if (x < 10) {
            c = x + '0';
        } else {
            c = x + 'A' - 10;
        }
        *(s.end() - i) = c;
        num = num / 16;
    }
    return s;
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
    int type) {

    LOG_DEBUG << "TicketController::getTickets";
    // 查找线路信息
    auto clientPtr = drogon::app().getDbClient();

    orm::Mapper<Line> trainMapper(clientPtr);
    // 异常已在filter处理
    Line lineStart = trainMapper.findOne(
        orm::Criteria(Line::Cols::_trip, orm::CompareOperator::EQ, trip) &&
        orm::Criteria(Line::Cols::_station, orm::CompareOperator::EQ, start));
    Line lineEnd = trainMapper.findOne(
        orm::Criteria(Line::Cols::_trip, orm::CompareOperator::EQ, trip) &&
        orm::Criteria(Line::Cols::_station, orm::CompareOperator::EQ, end));

    // 查找车票信息
    auto stationFlag = this->gnerateStationFlag(*lineStart.getPosition(),
                                                *lineEnd.getPosition());
    // 查找符合乘车区间并且按照余票数最大给出结果
    std::string sql =
        fmt::format("select * from ticket where trip='{}' and seatType={} "
                    "and stationFlag=~((~stationFlag)|{}) "
                    "order by available asc , carriage asc",
                    trip, type, this->numTo16Hex(stationFlag.to_ullong()));

    auto ticketList = clientPtr->execSqlSync(sql);

    Json::Value ret;
    ret["code"] = 0;
    if (ticketList.empty()) {
        ret["data"] = Json::arrayValue;
        ret["count"] = 0;
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
    std::function<void(const HttpResponsePtr &)> &&callback,
    OrderRequest &&order) {
    // 查找线路信息
    auto clientPtr = drogon::app().getDbClient();
    orm::Mapper<Line> lineMapper(clientPtr);
    Line lineStart, lineEnd;

    lineStart = lineMapper.findOne(
        orm::Criteria(Line::Cols::_trip, orm::CompareOperator::EQ,
                      order.trip) &&
        orm::Criteria(Line::Cols::_station, orm::CompareOperator::EQ,
                      order.start));
    lineEnd = lineMapper.findOne(
        orm::Criteria(Line::Cols::_trip, orm::CompareOperator::EQ,
                      order.trip) &&
        orm::Criteria(Line::Cols::_station, orm::CompareOperator::EQ,
                      order.end));

    // 查找车票信息
    auto stationFlag = this->gnerateStationFlag(*lineStart.getPosition(),
                                                *lineEnd.getPosition());
    // 查找符合乘车区间并且按照余票数最大给出结果
    std::string sql = fmt::format(
        "select * from ticket where trip='{}' and seatType={} "
        "and stationFlag=~((~stationFlag)|{}) "
        "order by available asc , carriage asc",
        order.trip, order.type, this->numTo16Hex(stationFlag.to_ullong()));

    auto ticketList = clientPtr->execSqlSync(sql);
    if (ticketList.empty()) {
        Json::Value ret;
        ret["code"] = 1;
        ret["msg"] = "No ticket";
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        callback(std::move(resp));
    }

    // 生成订单
    auto ticketRef = ticketList[0];
    orm::Mapper<TicketOrder> orderMapper(clientPtr);
    TicketOrder ticketOrder;
    ticketOrder.setTrip(order.trip);
    ticketOrder.setUsername(
        drogon::app().getPlugin<UserInfo>()->getInfo("username").asString());
    ticketOrder.setSeattype(order.type);
    // TODO: 车票价格计算
    ticketOrder.setAmount("10.58");
    ticketOrder.setStart(order.start);
    ticketOrder.setEnd(order.end);
    ticketOrder.setCarriage(ticketRef["carriage"].as<int>());
    ticketOrder.setSeatposition(ticketRef["seatPosition"].as<std::string>());
    orderMapper.insert(ticketOrder);

    // 更新车票信息
    LOG_DEBUG << "available:" << ticketRef["available"].as<std::string>();
    LOG_DEBUG << "stationFlag order:" << stationFlag.to_string();
    LOG_DEBUG << "new stationFlag:"
              << (stationFlag |
                  std::bitset<16>(
                      ticketRef["stationFlag"].as<unsigned short>()))
                     .to_string();
    std::bitset<16> stationFlagOld(
        ticketRef["stationFlag"].as<unsigned short>());
    sql = fmt::format(
        "update ticket set available=available-1, stationFlag={} where id={}",
        (stationFlagOld | stationFlag).to_ulong(), ticketRef["id"].as<int>());
    clientPtr->execSqlSync(sql);

    // return
    Json::Value ret;
    ret["code"] = 0;
    auto resp = HttpResponse::newHttpJsonResponse(ret);
    callback(std::move(resp));
}

void TicketController::refundTickets(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) {}

void TicketController::ticketInfo(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    const std::string &id) {

    orm::Mapper<TicketOrder> ticketOrderMapper(drogon::app().getDbClient());
    try {
        TicketOrder ticketOrder = ticketOrderMapper.findByPrimaryKey(stoi(id));
        if (drogon::app()
                .getPlugin<UserInfo>()
                ->getInfo("username")
                .asString() != *ticketOrder.getUsername()) {
            Json::Value ret;
            ret["code"] = 1;
            ret["data"] = "You can't see other's ticket";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
        }
        Json::Value ret;
        ret["code"] = 0;
        ret["data"] = ticketOrder.toJson();
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        callback(std::move(resp));
    } catch (orm::UnexpectedRows e) {
        Json::Value ret;
        ret["code"] = 1;
        ret["msg"] = "No ticket";
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        callback(std::move(resp));
    }
}