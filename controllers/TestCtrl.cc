#include "TestCtrl.h"
void TestCtrl::asyncHandleHttpRequest(const HttpRequestPtr &req,
                                      std::function<void (const HttpResponsePtr &)> &&callback)
{
    //write your application logic here
    auto resp=HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    // resp->setContentTypeCode(CT_TEXT_HTML);
    resp->setContentTypeCode(CT_APPLICATION_JSON);
    resp->setBody("{\"status\":\"ok\"}");
    callback(resp);
}