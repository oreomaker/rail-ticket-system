/**
 *
 *  UserInfo.h
 *  存放从token中获得的用户数据
 */

#pragma once

#include <drogon/plugins/Plugin.h>
#include <json/value.h>

class UserInfo : public drogon::Plugin<UserInfo> {
private:
    Json::Value info;
public:
    UserInfo() {}
    void initAndStart(const Json::Value &config) override;
    void shutdown() override;
    void setInfo(std::string &token);
    Json::Value &getInfo(std::string&& key);
};
