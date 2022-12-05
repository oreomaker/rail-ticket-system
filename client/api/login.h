#include <drogon/drogon.h>

#include <future>
#include <iostream>

using namespace drogon;

int nth_resp = 0;

class LoginClient{
public:
    LoginClient();
    ~LoginClient();
    void login(const std::string& username, const std::string& password);

};