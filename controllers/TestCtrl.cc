#include "TestCtrl.h"
void TestCtrl::asyncHandleHttpRequest(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) {
    // write your application logic here
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    // resp->setContentTypeCode(CT_TEXT_HTML);
    resp->setContentTypeCode(CT_APPLICATION_JSON);

    // write json string to response
    Json::Value root;
    root["message"] = "Hello, world!";
    Json::FastWriter writer;
    resp->setBody(writer.write(root));

    // show DB connection
    auto clientPtr = drogon::app().getDbClient();
    clientPtr->execSqlAsync(
        "select * from user where id=9",
        [](const drogon::orm::Result &result) {
            std::cout << result.size() << " rows selected!" << std::endl;
            int i = 0;
            for (auto row : result) {
                std::cout << i++ << ": user name is "
                          << row["username"].as<std::string>() << std::endl;
            }
        },
        [](const drogon::orm::DrogonDbException &e) {
            std::cerr << "error:" << e.base().what() << std::endl;
        },
        "default");

    callback(resp);
}