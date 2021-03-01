#include "AboutController.h"

void AboutController::asyncHandleHttpRequest(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback
)
{
    callback(drogon::HttpResponse::newHttpViewResponse("./views/about.csp"));
}