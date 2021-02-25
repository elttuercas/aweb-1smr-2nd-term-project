#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

/**
 * Class ContactController
 *
 * Handles displaying the contact form as well as handling its submission.
 *
 * @author Carlos Amores
 */
class ContactController : public drogon::HttpController<ContactController>
{
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(ContactController::get, "/contact/", HttpMethod::Get);
    METHOD_LIST_END

    void get(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
