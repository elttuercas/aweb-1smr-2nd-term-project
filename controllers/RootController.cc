#include "RootController.h"

void RootController::asyncHandleHttpRequest(
        const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback
)
{
    callback(drogon::HttpResponse::newHttpViewResponse("./views/index.csp"));
}