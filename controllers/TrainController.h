#pragma once

#include "models/Line.h"
#include "models/Train.h"
#include <drogon/HttpController.h>
#include <drogon/HttpTypes.h>

using namespace drogon;
using namespace drogon_model::rail_ticket;

class TrainController : public drogon::HttpController<TrainController> {
private:
    // 根据起始站点和终点站点查询直达列车
    orm::Result findTripByStation(const std::string &startStation,
                                  const std::string &endStation);
    // 根据起始站点和终点站点查询中转列车
    orm::Result findTransferTripByStation(const std::string &startStation,
                                          const std::string &endStation);

public:
    METHOD_LIST_BEGIN
    // 获取直达列车信息
    ADD_METHOD_TO(TrainController::getTrain, "/train?start={1}&end={2}", Get);
    // 获取中转列车信息
    ADD_METHOD_TO(TrainController::getTrainTransfer,
                  "/train-transfer?start={1}&end={2}", Get);
    // 获取列车信息
    ADD_METHOD_TO(TrainController::getTripInfo, "/trip?trip={1}", Get);
    METHOD_LIST_END

    void getTrain(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback,
                  const std::string &start, const std::string &end);
    void
    getTrainTransfer(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback,
                     const std::string &start, const std::string &end);
    void getTripInfo(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback,
                     const std::string &trip);
};
