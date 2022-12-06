#include "login.h"
#include <json/json.h>

void LoginClient::login(const std::string &username,
                        const std::string &password) {
    auto client = HttpClient::newHttpClient("http://localhost");
    auto req = HttpRequest::newHttpRequest();
    req->setMethod(drogon::Post);
    req->setPath("/user/login");

    Json::Value param;

    param["username"] = username;
    param["password"] = password;

    req->setBody("dd");

    client->sendRequest(
        req, [](ReqResult result, const HttpResponsePtr &response) {
            if (result != ReqResult::Ok) {
                std::cout << "error while sending request to server! result: "
                          << result << std::endl;
                return;
            }

            std::cout << "receive response!" << std::endl;
            // auto headers=response.
            std::cout << response->getBody() << std::endl;
            // auto cookies = response->cookies();
            // for (auto const &cookie : cookies) {
            //     std::cout << cookie.first << "=" << cookie.second.value()
            //               << ":domain=" << cookie.second.domain() << std::endl;
            // }
        });
}