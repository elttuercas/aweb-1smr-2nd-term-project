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
                // Create the view data and the alerts container.
                drogon::HttpViewData                            data;
                std::map<std::string, std::vector<std::string>> rgAlerts;
                // Check if there is an error from trying to view a non-existent message.
                if (req->session()->get<bool>("invalidMessage"))
                {
                    // Insert an error message into the alerts container.
                    rgAlerts["red"].push_back("El mensaje seleccionado no existe");
                    req->session()->erase("invalidMessage");
                }

                // Generate the formatted date for each model and store it in a map.
                std::map<std::string, std::string>                rgMessageDates;
                for (const drogon_model::sqlite3::ContactMessages &model : models)
                {
                    std::time_t ttMessageCreationTime   = std::chrono::system_clock::to_time_t(
                            std::chrono::time_point<std::chrono::system_clock>(
                                    std::chrono::seconds(*model.getSubmissionTs())
                            )
                    );
                    std::tm     *ptmMessageCreationTime = std::gmtime(&ttMessageCreationTime);
                    char        strFormattedTime[11];
                    std::strftime(strFormattedTime, sizeof(strFormattedTime), "%Y-%m-%d", ptmMessageCreationTime);
                    rgMessageDates[*model.getHash()] = std::string(strFormattedTime);
                }

                // Insert the found records and alert container into the view data.
                data.insert("contactMessages", models);
                data.insert("contactMessageDates", rgMessageDates);
                data.insert("alerts", rgAlerts);

                callback(drogon::HttpResponse::newHttpViewResponse("./views/messages/messages.csp", data));
            },
            [callback](const drogon::orm::DrogonDbException &exception)
            {
                drogon::HttpViewData                                data;
                std::map<std::string, std::vector<std::string>>     rgAlerts;
                std::vector<drogon_model::sqlite3::ContactMessages> rgContactMessages;
                std::map<std::string, std::string>                  rgMessageDates;

                rgAlerts["red"].push_back("Ha ocurrido un error, por favor intente acceder de nuevo más tarde");

                data.insert("contactMessages", rgContactMessages);
                data.insert("contactMessageDates", rgMessageDates);
                data.insert("alerts", rgAlerts);

                callback(drogon::HttpResponse::newHttpViewResponse("./views/messages/messages.csp", data));
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
                // Calculate human date from database model.
                std::time_t ttMessageCreationTime   = std::chrono::system_clock::to_time_t(
                        std::chrono::time_point<std::chrono::system_clock>(
                                std::chrono::seconds(*model.getSubmissionTs())
                        )
                );
                std::tm     *ptmMessageCreationTime = std::gmtime(&ttMessageCreationTime);
                char        strFormattedTime[11];
                std::strftime(strFormattedTime, sizeof(strFormattedTime), "%Y-%m-%d", ptmMessageCreationTime);

                // Create the view data and insert the data from the model.
                drogon::HttpViewData data;
                data.insert("messageID", *model.getId());
                data.insert("senderName", *model.getName());
                data.insert("senderSurname", *model.getSurname());
                data.insert("senderEmail", *model.getEmail());
                data.insert("message", *model.getMessage());
                data.insert("submissionDate", std::string(strFormattedTime));

                callback(drogon::HttpResponse::newHttpViewResponse("./views/messages/view.csp", data));
            },
            [callback, &req](const drogon::orm::DrogonDbException &exception)
            {
                req->session()->insert("invalidMessage", true);
                callback(drogon::HttpResponse::newRedirectionResponse("/contact/messages/"));
            }
    );
}
