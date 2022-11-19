#pragma once

#include "../models/User.h"
#include <drogon/HttpAppFramework.h>
#include <drogon/HttpController.h>
#include <drogon/orm/Criteria.h>
#include <drogon/orm/Mapper.h>
#include <jsoncpp/json/value.h>
#include <trantor/utils/Logger.h>
#include <jwt-cpp/jwt.h>

using namespace drogon;
using namespace drogon_model::rail_ticket;

struct UserRequest {
    std::string userName;
    std::string password;
};

class UserController : public drogon::HttpController<UserController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(UserController::login, "/user/login", Post);
    ADD_METHOD_TO(UserController::registerUser, "/user/register", Post);
    ADD_METHOD_TO(UserController::listUser, "/user/list", Get, "LoginFilter");
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