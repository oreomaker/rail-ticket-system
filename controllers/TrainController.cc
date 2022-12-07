#include "TrainController.h"
#include <trantor/utils/Logger.h>

orm::Result TrainController::findTripByStation(const std::string &startStation,
                                               const std::string &endStation) {
    auto clientPtr = drogon::app().getDbClient();
    std::string sql = "select l1.trip as trip from line as l1, line as l2"
                      " where l1.station='";
    sql += startStation;
    sql += "'and l2.station='";
    sql += endStation;
    sql += "' and l1.trip=l2.trip and l1.position<l2.position";

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
    std::string sql1 = "select l1.trip as trip1, l3.trip as trip2, l2.station "
                       "as interStation, l2.arrive_time as interArriveTime, "
                       "l3.leaving_time as interLeavingTime "
                       "from line as l1, line as l2, line as l3, line l4 "
                       "where l1.station='";
    std::string sql2 = "' and l4.station='";
    std::string sql3 =
        "' and l1.trip=l2.trip and l3.trip=l4.trip and l1.trip!=l3.trip"
        " and l1.position<l2.position and l3.position<l4.position"
        " and l2.station=l3.station and l2.arrive_time<l3.leaving_time";

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

    // generate the transfer train info
    auto clientPtr = drogon::app().getDbClient();
    orm::Mapper<Train> mapper(clientPtr);

    Json::Value ret, trip;
    for (auto &row : tripList) {
        // trip1
        auto train1 = mapper.findOne(
            orm::Criteria(Train::Cols::_trip, orm::CompareOperator::EQ,
                          row["trip1"].as<std::string>()));
        trip["trip1"] = train1.toJson();
        // trip2
        auto train2 = mapper.findOne(
            orm::Criteria(Train::Cols::_trip, orm::CompareOperator::EQ,
                          row["trip2"].as<std::string>()));
        trip["trip2"] = train2.toJson();
        trip["interStation"] = row["interStation"].as<std::string>();
        trip["interArriveTime"] = row["interArriveTime"].as<std::string>();
        trip["interLeavingTime"] = row["interLeavingTime"].as<std::string>();

        ret["data"].append(trip);
    }

    // build response
    ret["code"] = 0;
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