/**
 *
 *  LoginFilter.cc
 *
 */

#include "LoginFilter.h"
#include <trantor/utils/Logger.h>

using namespace drogon;

void LoginFilter::doFilter(const HttpRequestPtr &req, FilterCallback &&fcb,
                           FilterChainCallback &&fccb) {
    LOG_INFO << "LoginFilter";
    auto token = req->getHeader("Authorization");
    try {
        auto decoded = jwt::decode(token);
        // Passed
        fccb();
        return;
    } catch (std::exception e) {
        LOG_INFO << "LoginFilter failed";
        Json::Value ret;
        ret["status"] = 1;
        ret["message"] = "No Authorization";
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k401Unauthorized);
        fcb(resp);
        return;
    }
}
