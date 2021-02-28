#include "Api_Messages.h"

using namespace Api;

void Messages::handleQuery(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback,
        const std::string &query,
        const int &queryType
)
{
    static const std::map<int, std::string> rgQueryTypesToCols = {
            {1, drogon_model::sqlite3::ContactMessages::Cols::_name},
            {2, drogon_model::sqlite3::ContactMessages::Cols::_surname},
            {3, drogon_model::sqlite3::ContactMessages::Cols::_email}
    };

    drogon::orm::Mapper<drogon_model::sqlite3::ContactMessages> contactMessagesMapper(drogon::app().getDbClient());
    try
    {
        contactMessagesMapper.findBy(
                drogon::orm::Criteria(
                        rgQueryTypesToCols.at(queryType),
                        drogon::orm::CompareOperator::Like,
                        query + '%'
                ),
                [callback](const std::vector<drogon_model::sqlite3::ContactMessages> &result)
                {
                    // Convert the objects to JSON values to be sent to the client.
                    Json::Value                                       jsonRoot = Json::Value(Json::arrayValue);
                    for (const drogon_model::sqlite3::ContactMessages &row : result)
                    {
                        jsonRoot.append(row.toJson());
                    }
                    // Return them to the client.
                    callback(drogon::HttpResponse::newHttpJsonResponse(jsonRoot));
                },
                [callback](const drogon::orm::DrogonDbException &exception)
                {
                    // If the query fails for some reason, send a 500 error response and handle it client side.
                    drogon::HttpResponsePtr resp = drogon::HttpResponse::newHttpResponse();
                    resp->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
                    resp->setContentTypeCode(drogon::ContentType::CT_NONE);
                    callback(resp);
                }
        );
    }
    catch (const std::out_of_range &)
    {
        // And if the user sends a query type that is not 1, 2 or 3. Return a bad request error response.
        drogon::HttpResponsePtr resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::HttpStatusCode::k400BadRequest);
        resp->setContentTypeCode(drogon::ContentType::CT_NONE);
        callback(resp);
    }
}

void Messages::deleteMessage(
        const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback,
        const std::string &hash
)
{
    drogon::orm::Mapper<drogon_model::sqlite3::ContactMessages> contactMessagesMapper(drogon::app().getDbClient());
    // Attempt to delete the requested model.
    contactMessagesMapper.deleteBy(
            drogon::orm::Criteria(
                    drogon_model::sqlite3::ContactMessages::Cols::_hash,
                    drogon::orm::CompareOperator::EQ,
                    hash
            ),
            [callback](const size_t &deletedRows)
            {
                drogon::HttpResponsePtr resp = drogon::HttpResponse::newHttpResponse();
                resp->setContentTypeCode(drogon::ContentType::CT_NONE);

                if (deletedRows == 0)
                {
                    // If no rows were deleted, the specified record does not exist. Therefore, 400 error.
                    resp->setStatusCode(drogon::HttpStatusCode::k400BadRequest);
                    callback(resp);
                }
                else
                {
                    resp->setStatusCode(drogon::HttpStatusCode::k204NoContent);
                    callback(resp);
                }
            },
            [callback](const drogon::orm::DrogonDbException &exception)
            {
                drogon::HttpResponsePtr resp;
                resp->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
                resp->setContentTypeCode(drogon::ContentType::CT_NONE);
                callback(resp);
            }
    );
}
