#pragma once

#include "../models/User.h"
#include <drogon/HttpAppFramework.h>
#include <drogon/HttpController.h>
#include <drogon/orm/Mapper.h>
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
    // METHOD_ADD(User::getInfo, "/{1}/info?token={2}", Get, "LoginFilter");
    METHOD_LIST_END
    void login(const HttpRequestPtr &req,
               std::function<void(const HttpResponsePtr &)> &&callback,
               UserRequest &&user);
    void registerUser(const HttpRequestPtr &req,
                      std::function<void(const HttpResponsePtr &)> &&callback,
                      std::string &&username, std::string &&password);
};

namespace drogon
{
template <>
inline UserRequest fromRequest(const HttpRequest &req)
{
    auto json = req.getJsonObject();
    // LOG_DEBUG << (*json)["username"].asString();
    UserRequest user;
    if(json)
    {
        user.userName = ((*json)["username"].asString());
        user.password = ((*json)["password"].asString());
    }
    else LOG_DEBUG << "json is null";
    return user;
}

}