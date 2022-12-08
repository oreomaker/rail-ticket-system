/**
 *
 *  AdminFilter.h
 *  管理员过滤器，必须用在LoginFilter之后
 */

#pragma once

#include "plugins/UserInfo.h"
#include <drogon/HttpAppFramework.h>
#include <drogon/HttpFilter.h>
using namespace drogon;

class AdminFilter : public HttpFilter<AdminFilter> {
public:
    AdminFilter() {}
    void doFilter(const HttpRequestPtr &req, FilterCallback &&fcb,
                  FilterChainCallback &&fccb) override;
};
