#include "TrainController.h"
#include <trantor/utils/Logger.h>

orm::Result TrainController::findTripByStation(const std::string &startStation,
                                               const std::string &endStation) {
    auto clientPtr = drogon::app().getDbClient();
    std::string sql = "select t1.trip as line1, t2.trip as line2 from line as "
                      "t1, line as t2 where t1.station='";
    sql += startStation;
    sql += "'and t2.station='";
    sql += endStation;
    sql += "'and t1.trip=t2.trip and t1.position<t2.position";
    try {
        return clientPtr->execSqlSync(sql);
    } catch (const orm::DrogonDbException &e) {
        LOG_ERROR << e.base().what();
        return orm::Result(nullptr);
    }
}

orm::Result
TrainController::findTransferTripByStation(const std::string &startStation,
                                           const std::string &endStation) {
    auto clientPtr = drogon::app().getDbClient();
    std::string sql1 = "select t1.trip as trip1, t2.trip as trip2"
                       "from line as t1, line as t2, line as t3, line t4"
                       "where t1.station='";
    std::string sql2 = "'and t4.station='";
    std::string sql3 =
        "'and t1.trip=t2.trip and t3.trip=t4.trip and t1.trip!=t3.trip"
        " and t1.position<t2.position and t3.position<t4.position"
        " and t2.station=t3.station and t2.arrive_time<t3.leave_time";

    std::string sql;
    sql += sql1;
    sql += startStation;
    sql += sql2;
    sql += endStation;
    sql += sql3;

    try {
        return clientPtr->execSqlSync(sql);
    } catch (const orm::DrogonDbException &e) {
        LOG_ERROR << e.base().what();
        return orm::Result(nullptr);
    }
}

void TrainController::getTrain(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    const std::string &start, const std::string &end) {

    // get available train trips by start and end
    auto tripList = this->findTripByStation(start, end);
    std::vector<std::string> trips;
    // if no trip found, return empty list
    if (tripList.empty()) {
        Json::Value ret;
        ret["code"] = 0;
        ret["data"] = Json::arrayValue;
        return callback(HttpResponse::newHttpJsonResponse(std::move(ret)));
    }
    // build trip list
    for (auto &row : tripList) {
        trips.push_back(row["trip"].as<std::string>());
    }

    // get train info by trip list
    auto clientPtr = drogon::app().getDbClient();
    orm::Mapper<Train> mapper(clientPtr);
    auto trainList = mapper.findBy(
        orm::Criteria(Train::Cols::_trip, orm::CompareOperator::In, trips));

    // build response
    Json::Value ret;
    ret["code"] = 0;
    for (auto &station : trainList) {
        ret["data"].append(station.toJson());
    }
    return callback(HttpResponse::newHttpJsonResponse(std::move(ret)));
}

void TrainController::getTrainTransfer(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    const std::string &start, const std::string &end) {

    // get available train trips by start and end
    auto tripList = this->findTransferTripByStation(start, end);
    std::vector<std::string> trips;
    // if no trip found, return empty list
    if (tripList.empty()) {
        Json::Value ret;
        ret["code"] = 0;
        ret["data"] = Json::arrayValue;
        return callback(HttpResponse::newHttpJsonResponse(std::move(ret)));
    }
    // build trip list
    for (auto &row : tripList) {
        trips.push_back(row["trip"].as<std::string>());
    }

    // get train info by trip list
    auto clientPtr = drogon::app().getDbClient();
    orm::Mapper<Train> mapper(clientPtr);
    auto trainList = mapper.findBy(
        orm::Criteria(Train::Cols::_trip, orm::CompareOperator::In, trips));

    // build response
    Json::Value ret;
    ret["code"] = 0;
    for (auto &station : trainList) {
        ret["data"].append(station.toJson());
    }
    return callback(HttpResponse::newHttpJsonResponse(std::move(ret)));
}

void TrainController::getTripInfo(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    const std::string &trip) {

    auto clientPtr = drogon::app().getDbClient();
    orm::Mapper<Line> mapper(clientPtr);
    auto tripList = mapper.orderBy(Line::Cols::_position)
                        .findBy(orm::Criteria(Line::Cols::_trip,
                                              orm::CompareOperator::EQ, trip));

    Json::Value ret;
    ret["code"] = 0;
    for (auto &station : tripList) {
        ret["data"].append(station.toJson());
    }
    return callback(HttpResponse::newHttpJsonResponse(std::move(ret)));
}