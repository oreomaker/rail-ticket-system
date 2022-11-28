/**
 *
 *  UserInfo.cc
 *
 */

#include "UserInfo.h"
#include <string>

using namespace drogon;

void UserInfo::initAndStart(const Json::Value &config) {
    /// Initialize and start the plugin
}

void UserInfo::shutdown() {
    /// Shutdown the plugin
}

void UserInfo::setInfo(std::string &token) {
    Json::Reader parser;
    parser.parse(token, this->info);
}

Json::Value &UserInfo::getInfo(std::string &&key) { return this->info[key]; }