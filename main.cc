#include <drogon/HttpAppFramework.h>
#include <drogon/utils/FunctionTraits.h>
int main() {
    std::cout << "     _\n"
              << "  __| |_ __ ___   __ _  ___  _ __\n"
              << " / _` | '__/ _ \\ / _` |/ _ \\| '_ \\\n"
              << "| (_| | | | (_) | (_| | (_) | | | |\n"
              << " \\__,_|_|  \\___/ \\__, |\\___/|_| |_|\n"
              << "                 |___/" << std::endl;
    std::cout << "Drogon version: " << drogon::getVersion() << std::endl;
    // Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0", 80);
    // Load config file
    drogon::app().loadConfigFile("../config.json");
    drogon::app().registerPostHandlingAdvice(
        [](const drogon::HttpRequestPtr &req,
           const drogon::HttpResponsePtr &resp) {
            resp->addHeader("Access-Control-Allow-Origin", "*");
        });

    // Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}