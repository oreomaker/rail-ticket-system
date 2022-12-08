/**
 *
 *  AdminFilter.cc
 *
 */

#include "AdminFilter.h"

using namespace drogon;

void AdminFilter::doFilter(const HttpRequestPtr &req, FilterCallback &&fcb,
                           FilterChainCallback &&fccb) {
    LOG_INFO << "AdminFilter";
    try {
        auto *userInfoPlug = drogon::app().getPlugin<UserInfo>();
        auto user = userInfoPlug->getInfo("username").asString();
        LOG_INFO << "user: " << user;
        // TODO: use user type not username
        if (user != "admin") {
            throw std::exception();
        }
        fccb(); // Passed
        return;
    } catch (std::exception e) {
        LOG_INFO << "AdminFilter failed";
        Json::Value ret;
        ret["code"] = 1;
        ret["message"] = "Permision denied";
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k401Unauthorized);
        fcb(resp);
        return;
    }
}
