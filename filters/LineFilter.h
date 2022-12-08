/**
 *
 *  LineFilter.h
 *  在线路相关业务前对起始站点进行校验, 用于含有trip，start，end参数的Get请求
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;

class LineFilter : public HttpFilter<LineFilter> {
public:
    LineFilter() {}
    void doFilter(const HttpRequestPtr &req, FilterCallback &&fcb,
                  FilterChainCallback &&fccb) override;
};
