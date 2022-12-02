#include "TrainController.h"
#include <trantor/utils/Logger.h>

void TrainController::getTrain(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    const std::string &start, const std::string &end) {

    LOG_INFO << "getTrain";
    LOG_INFO << start << " " << end;
    orm::Mapper<Line> mapper(drogon::app().getDbClient());
    auto list = mapper.
    findBy(
        orm::Criteria(Line::Cols::_station, orm::CompareOperator::EQ, start) ||
        orm::Criteria(Line::Cols::_station, orm::CompareOperator::EQ, end));

    Json::Value ret;
    ret["code"] = 0;
    for (auto &station : list) {
        ret["data"].append(station.toJson());
        LOG_INFO << station.toJson().toStyledString();
    }
    return callback(HttpResponse::newHttpJsonResponse(std::move(ret)));
}