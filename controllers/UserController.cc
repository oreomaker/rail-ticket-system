#include "UserController.h"
#include <cstddef>

void UserController::login(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    UserRequest &&user) {

    LOG_DEBUG << "login: " << user.userName << " " << user.password;
    orm::Mapper<User> mapper(drogon::app().getDbClient());

    try {
        auto result = mapper.findOne(orm::Criteria(
            User::Cols::_username, orm::CompareOperator::EQ, "user.userName"));
    } catch (orm::UnexpectedRows e) {
        Json::Value ret;
        ret["status"] = 1;
        ret["message"] = "User not found";
        return callback(HttpResponse::newHttpJsonResponse(ret));
    }

    Json::Value ret;
    ret["code"] = 0;

    return callback(HttpResponse::newHttpJsonResponse(ret));
}

void UserController::registerUser(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    UserRequest &&user) {

    LOG_DEBUG << "registerUser: " << user.userName << " " << user.password;
    orm::Mapper<User> mapper(drogon::app().getDbClient());

    User newUser;
    newUser.setUsername(user.userName);
    newUser.setPassword(user.password);
    mapper.insert(newUser);

    Json::Value res;
    res["status"] = 0;
    return callback(HttpResponse::newHttpJsonResponse(res));
}

void UserController::listUser(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) {

    orm::Mapper<User> mapper(drogon::app().getDbClient());
    auto list = mapper.findAll();

    Json::Value res;
    res["status"] = 0;
    for (auto &user : list) {
        res["data"].append(user.toJson());
    }
    return callback(HttpResponse::newHttpJsonResponse(res));
}