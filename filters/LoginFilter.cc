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
    // Edit your logic here
    if (1) {
        // Passed
        fccb();
        return;
    }
    // Check failed
    auto res = drogon::HttpResponse::newHttpResponse();
    res->setStatusCode(k500InternalServerError);
    fcb(res);
}
