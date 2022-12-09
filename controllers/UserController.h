#pragma once

#include "models/User.h"
#include <drogon/HttpAppFramework.h>
#include <drogon/HttpController.h>
#include <drogon/orm/Criteria.h>
#include <drogon/orm/Mapper.h>
#include <json/value.h>
#include <jwt-cpp/jwt.h>
#include <trantor/utils/Logger.h>

using namespace drogon;
using namespace drogon_model::rail_ticket;

struct UserRequest { // 用于接收用户注册和登录请求
    std::string userName;
    std::string password;
};

class UserController : public drogon::HttpController<UserController> {
public:
    METHOD_LIST_BEGIN
    // 用户登录
    ADD_METHOD_TO(UserController::login, "/user/login", Post);
    // 用户注册
    ADD_METHOD_TO(UserController::registerUser, "/user/register", Post);
    // 获取用户列表
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