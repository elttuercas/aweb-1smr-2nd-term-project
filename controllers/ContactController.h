#pragma once

#include <drogon/HttpController.h>
#include "models/ContactMessages.h"

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
        ADD_METHOD_TO(ContactController::post, "/contact/", HttpMethod::Post);
    METHOD_LIST_END

    /**
     * Display the contact form.
     * @param req
     * @param callback
     */
    void get(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    /**
     * Validate the request contents server-side and store the form data in a database.
     * @param req
     * @param callback
     */
    void post(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
