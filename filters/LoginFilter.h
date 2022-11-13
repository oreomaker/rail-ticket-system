/**
 *
 *  LoginFilter.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;

class LoginFilter : public HttpFilter<LoginFilter> {
public:
    LoginFilter() {}
    void doFilter(const HttpRequestPtr &req, FilterCallback &&zzfcb,
                  FilterChainCallback &&fccb) override;
};
