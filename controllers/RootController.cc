#include "RootController.h"

void RootController::asyncHandleHttpRequest(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback
)
{
    callback(drogon::HttpResponse::newHttpViewResponse("./views/index.csp"));
}