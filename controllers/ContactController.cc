#include "ContactController.h"

void ContactController::get(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback
)
{
    callback(drogon::HttpResponse::newHttpViewResponse("./views/contact.csp"));
}
