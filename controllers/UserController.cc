#include "UserController.h"
#include "jwt-cpp/jwt.h"
#include "jwt-cpp/traits/kazuho-picojson/defaults.h"

void UserController::login(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    UserRequest &&user) {

    LOG_DEBUG << "login: " << user.userName << " " << user.password;
    orm::Mapper<User> mapper(drogon::app().getDbClient());

    try {
        auto result = mapper.findOne(orm::Criteria(
            User::Cols::_username, orm::CompareOperator::EQ, user.userName));
        if (result.getValueOfPassword() == user.password) {
            LOG_DEBUG << "login success";
            // create jwt token
            auto token =
                jwt::create()
                    .set_issuer("auth0")
                    .set_type("JWT")
                    .set_issued_at(std::chrono::system_clock::now())
                    .set_expires_at(std::chrono::system_clock::now() +
                                    std::chrono::seconds(3600))
                    .set_payload_claim("username",
                                       jwt::claim(std::string(user.userName)))
                    .sign(jwt::algorithm::hs256{"secret123456"});

            Json::Value ret;
            ret["code"] = 0;
            ret["token"] = token;
            return callback(HttpResponse::newHttpJsonResponse(ret));
        } else {
            LOG_DEBUG << "login failed";
            Json::Value ret;
            ret["code"] = 1;
            ret["message"] = "wrong password";
            return callback(HttpResponse::newHttpJsonResponse(ret));
        }
    } catch (orm::UnexpectedRows e) {
        Json::Value ret;
        ret["status"] = 1;
        ret["message"] = "User Not Found";
        return callback(HttpResponse::newHttpJsonResponse(ret));
    }
}

void UserController::registerUser(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    UserRequest &&user) {

    LOG_DEBUG << "registerUser: " << user.userName << " " << user.password;
    orm::Mapper<User> mapper(drogon::app().getDbClient());

    try {
        auto result = mapper.findOne(orm::Criteria(
            User::Cols::_username, orm::CompareOperator::EQ, user.userName));
        Json::Value ret;
        ret["status"] = 1;
        ret["message"] = "user has been registered";
        return callback(HttpResponse::newHttpJsonResponse(ret));
    } catch (orm::UnexpectedRows e) {
        User newUser;
        newUser.setUsername(user.userName);
        newUser.setPassword(user.password);
        mapper.insert(newUser);

        Json::Value res;
        res["status"] = 0;
        return callback(HttpResponse::newHttpJsonResponse(res));
    }
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