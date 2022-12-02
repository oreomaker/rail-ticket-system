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
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(TrainController::getTrain, "/train?start={1}&end={2}", Get);
    METHOD_LIST_END
    void getTrain(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback,
                  const std::string &start, const std::string &end);
};
