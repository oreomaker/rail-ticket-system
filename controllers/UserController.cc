#include "UserController.h"
#include <jsoncpp/json/value.h>
#include <trantor/utils/Logger.h>

void UserController::login(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    UserRequest &&user) {
    // LOG_DEBUG << "login: " << *user.getUsername() << " " << *user.getPassword();
    LOG_DEBUG << "login: " << user.userName << " " << user.password;
    orm::Mapper<User> mapper(drogon::app().getDbClient());
    auto list = mapper.findAll();
    Json::Value res;
    res["code"] = 0;
    for(auto &user : list) {
        res["data"].append(user.toJson());
    }
    return callback(HttpResponse::newHttpJsonResponse(res));
}

void UserController::registerUser(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    std::string &&username, std::string &&password) {
    
    orm::Mapper<User> mapper(drogon::app().getDbClient());
    auto list = mapper.findAll();
    Json::Value res;
    res["code"] = 0;
    return callback(HttpResponse::newHttpJsonResponse(res));
}