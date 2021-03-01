#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class AboutController : public drogon::HttpSimpleController<AboutController>
{
public:
    void
    asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;

    PATH_LIST_BEGIN
        PATH_ADD("/about/", HttpMethod::Get);
    PATH_LIST_END
};
