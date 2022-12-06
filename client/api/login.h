#include <drogon/HttpAppFramework.h>
#include <drogon/drogon.h>

#include <future>
#include <iostream>

using namespace drogon;

class LoginClient {
public:
    LoginClient();
    ~LoginClient();
    void login(const std::string &username, const std::string &password);
};