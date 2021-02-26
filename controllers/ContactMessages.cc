#include "ContactMessages.h"

void ContactMessages::get(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback
)
{
    // Retrieve all of the database records.
    drogon::orm::Mapper<drogon_model::sqlite3::ContactMessages> contactMessagesMapper(drogon::app().getDbClient());
    contactMessagesMapper.findAll(
            [callback, &req](const std::vector<drogon_model::sqlite3::ContactMessages> &models)
            {
                // Create the view data and insert the found records.
                drogon::HttpViewData data;
                data.insert("contactMessages", models);
                data.insert("invalidMessage", req->session()->get<bool>("invalidMessage"));

                callback(
                        drogon::HttpResponse::newHttpViewResponse("./views/messages/messages.csp", data)
                );
            },
            [](const drogon::orm::DrogonDbException &exception)
            {

            }
    );
}

void ContactMessages::getMessage(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback,
        const std::string &msgHash
)
{
    // Attempt to load the message first and foremost.
    drogon::orm::Mapper<drogon_model::sqlite3::ContactMessages> contactMessagesMapper(drogon::app().getDbClient());
    contactMessagesMapper.findOne(
            drogon::orm::Criteria(
                    drogon_model::sqlite3::ContactMessages::Cols::_hash,
                    drogon::orm::CompareOperator::EQ,
                    msgHash
            ),
            [callback](const drogon_model::sqlite3::ContactMessages &model)
            {
                // Create the view data and insert the data from the model.
                drogon::HttpViewData data;
                data.insert("messageID", *model.getId());
                data.insert("senderName", *model.getName());
                data.insert("senderSurname", *model.getSurname());
                data.insert("senderEmail", *model.getEmail());
                data.insert("message", *model.getMessage());

                callback(
                        drogon::HttpResponse::newHttpViewResponse("./views/messages/view.csp", data)
                );
            },
            [callback, &req](const drogon::orm::DrogonDbException &exception)
            {
                // Set a flag to display an error after redirecting.
                req->session()->insert("invalidMessage", true);
                callback(drogon::HttpResponse::newRedirectionResponse("/contact/messages/"));
            }
    );
}
