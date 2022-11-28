/**
 *
 *  LoginFilter.cc
 *
 */

#include "LoginFilter.h"
#include "plugins/UserInfo.h"
#include <drogon/HttpAppFramework.h>
#include <json/reader.h>
#include <json/value.h>
#include <trantor/utils/Logger.h>

using namespace drogon;

void LoginFilter::doFilter(const HttpRequestPtr &req, FilterCallback &&fcb,
                           FilterChainCallback &&fccb) {
    LOG_INFO << "LoginFilter";
    auto token = req->getHeader("Authorization");
    try {
        auto decoded = jwt::decode(token).get_payload();
        LOG_INFO << "decoded: " << decoded;
        auto *userInfoPlug = drogon::app().getPlugin<UserInfo>();
        userInfoPlug->setInfo(decoded);
        LOG_INFO << "info: " << userInfoPlug->getInfo("username").asString();
        fccb(); // Passed
        return;
    } catch (std::exception e) {
        LOG_INFO << "LoginFilter failed";
        Json::Value ret;
        ret["code"] = 1;
        ret["message"] = "No Authorization";
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k401Unauthorized);
        fcb(resp);
        return;
    }
}
