#pragma once

#include <drogon/HttpController.h>
#include "models/ContactMessages.h"

using namespace drogon;
namespace Api
{
    /**
     * Class Messages
     *
     * API class to handle operations related to contact messages sent by users.
     *
     * @author Carlos Amores
     */
    class Messages : public drogon::HttpController<Messages>
    {
    public:
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(Messages::handleQuery, "/api/messages/?q={1:query}&qt={2:queryType}", HttpMethod::Get);
            ADD_METHOD_TO(Messages::deleteMessage, "/api/messages/delete/{1:hash}/", HttpMethod::Delete);
        METHOD_LIST_END

        /**
         * Handle a GET query about the messages stored in the database and return them as a JSON object.
         * @param req
         * @param callback
         * @param query
         * @param queryType
         */
        void handleQuery(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                         const std::string &query, const int &queryType);
        /**
         * Handle a DELETE request to remove a message from the database.
         * @param req
         * @param callback
         * @param hash
         */
        void deleteMessage(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                           const std::string &hash);
    };
}
