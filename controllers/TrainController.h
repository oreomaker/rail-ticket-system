#pragma once

#include "models/Line.h"
#include "models/Train.h"
#include <drogon/HttpController.h>
#include <drogon/HttpTypes.h>

using namespace drogon;
using namespace drogon_model::rail_ticket;

class TrainController : public drogon::HttpController<TrainController> {
private:
    orm::Result findTripByStation(const std::string &startStation, const std::string &endStation);
    orm::Result findTransferTripByStation(const std::string &startStation, const std::string &endStation);
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(TrainController::getTrain, "/train?start={1}&end={2}", Get);
    ADD_METHOD_TO(TrainController::getTrainTransfer, "/train-transfer?start={1}&end={2}", Get);
    ADD_METHOD_TO(TrainController::getTripInfo, "/trip?trip={1}", Get);
    METHOD_LIST_END

    // 根据起始站和终点站查询列车
    void getTrain(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback,
                  const std::string &start, const std::string &end);
    // 根据起始站和终点站查询可以中转的列车
    void getTrainTransfer(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback,
                  const std::string &start, const std::string &end);
    // 根据列车号查询列车信息
    void getTripInfo(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback,
                  const std::string &trip);
};
