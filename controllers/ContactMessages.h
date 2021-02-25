#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

/**
 * Class ContactMessages
 *
 * This class handles displaying all of the existent contact messages as well as viewing specific ones.
 *
 * @author Carlos Amores
 */
class ContactMessages : public drogon::HttpController<ContactMessages>
{
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(ContactMessages::get, "/contact/messages/", HttpMethod::Get);
    METHOD_LIST_END

    /**
     * Display a table with all the submitted contact messages.
     * @param req
     * @param callback
     */
    void get(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
};
