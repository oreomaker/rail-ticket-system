#pragma once

#include "../models/User.h"
#include <drogon/HttpAppFramework.h>
#include <drogon/HttpController.h>
#include <drogon/orm/Criteria.h>
#include <drogon/orm/Mapper.h>
#include <jsoncpp/json/value.h>
#include <trantor/utils/Logger.h>

using namespace drogon;
using namespace drogon_model::rail_ticket;

struct UserRequest {
    std::string userName;
    std::string password;
};

class UserController : public drogon::HttpController<UserController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(UserController::login, "/user/login", Post, Get);
    METHOD_ADD(UserController::registerUser, "/token?userId={1}&passwd={2}",
               Post);
    METHOD_ADD(UserController::listUser, "/list", Get, "LoginFilter");
    METHOD_LIST_END

    void login(const HttpRequestPtr &req,
               std::function<void(const HttpResponsePtr &)> &&callback,
               UserRequest &&user);
    void registerUser(const HttpRequestPtr &req,
                      std::function<void(const HttpResponsePtr &)> &&callback,
                      UserRequest &&user);
    void listUser(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback);
};

namespace drogon {
template <> inline UserRequest fromRequest(const HttpRequest &req) {
    auto json = req.getJsonObject();
    UserRequest user;
    if (json) {
        user.userName = ((*json)["username"].asString());
        user.password = ((*json)["password"].asString());
    }
    return user;
}

} // namespace drogon