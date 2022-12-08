/**
 *
 *  LineFilter.cc
 *
 */

#include "LineFilter.h"
#include "models/Line.h"
#include <drogon/HttpAppFramework.h>

using namespace drogon;
using namespace drogon_model::rail_ticket;

void LineFilter::doFilter(const HttpRequestPtr &req, FilterCallback &&fcb,
                          FilterChainCallback &&fccb) {

    orm::Mapper<Line> trainMapper(drogon::app().getDbClient());
    std::string trip = req->getParameter("trip"), start = req->getParameter("start"), end = req->getParameter("end");
    Line lineStart, lineEnd;
    try {
        lineStart = trainMapper.findOne(
            orm::Criteria(Line::Cols::_trip, orm::CompareOperator::EQ, trip) &&
            orm::Criteria(Line::Cols::_trip, orm::CompareOperator::EQ, start));
        lineEnd = trainMapper.findOne(
            orm::Criteria(Line::Cols::_trip, orm::CompareOperator::EQ, trip) &&
            orm::Criteria(Line::Cols::_trip, orm::CompareOperator::EQ, end));
    } catch (orm::UnexpectedRows e) { // 未找到线路信息
        Json::Value ret;
        ret["code"] = 1;
        ret["msg"] = "Invalid trip or start or end";
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        fcb(std::move(resp));
        return;
    }
    // 判断起点和终点是否合法
    if (*lineStart.getPosition() > *lineEnd.getPosition()) {
        Json::Value ret;
        ret["code"] = 1;
        ret["msg"] = "Invalid trip or start or end";
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        fcb(std::move(resp));
        return;
    }

    // Passed
    fccb();
    return;
}
