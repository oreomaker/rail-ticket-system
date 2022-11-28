/**
 *
 *  UserInfo.h
 *
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
