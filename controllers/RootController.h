#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

/**
 * Class RootController
 *
 * Handles displaying the view seen by default when accessing the site.
 *
 * @author Carlos Amores
 */
class RootController : public drogon::HttpSimpleController<RootController>
{
public:
    void
    asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;

    PATH_LIST_BEGIN
        PATH_ADD("/", HttpMethod::Get);
    PATH_LIST_END
};
