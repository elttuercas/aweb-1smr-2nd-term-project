#include "ContactController.h"

void ContactController::get(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback
)
{
    callback(drogon::HttpResponse::newHttpViewResponse("./views/contact.csp"));
}

void ContactController::post(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback
)
{
    const std::unordered_map<std::string, std::string> rgPostData = req->getParameters();

    std::vector<std::string> rgExpectedParams = {
            "name",
            "surname",
            "email",
            "message"
    };

    std::vector<std::string> rgInputParams;
    try
    {
        rgInputParams.reserve(rgPostData.size());
    }
    catch (const std::length_error &)
    {
        /*
         * A malicious user could cause a length_error by submitting a form with more elements than
         * std::vector<std::string>::max_size so this catch block should redirect the user back to the
         * contact form.
         */
        callback(drogon::HttpResponse::newRedirectionResponse("/contact/"));
        return;
    }

    for (const std::pair<const std::string, std::string> &datum : rgPostData)
    {
        rgInputParams.push_back(datum.first);
    }

    // Sort both vectors and ensure the keys match.
    std::sort(rgInputParams.begin(), rgInputParams.end());
    std::sort(rgExpectedParams.begin(), rgExpectedParams.end());

    if (rgInputParams != rgExpectedParams)
    {
        callback(drogon::HttpResponse::newRedirectionResponse("/contact/"));
        return;
    }

    // All good so far, create the database record.
    drogon::orm::Mapper<drogon_model::sqlite3::ContactMessages> contactMessagesMapper(drogon::app().getDbClient());

    drogon_model::sqlite3::ContactMessages contactMessage;
    contactMessage.setName(rgPostData.at("name"));
    contactMessage.setSurname(rgPostData.at("surname"));
    contactMessage.setEmail(rgPostData.at("email"));
    contactMessage.setMessage(rgPostData.at("message"));

    // Get the current unix timestamp.
    std::chrono::time_point<std::chrono::system_clock> tpNow = std::chrono::system_clock::now();

    long iEpochTimestamp = std::chrono::duration_cast<std::chrono::seconds>(tpNow.time_since_epoch()).count();

    // Set the timestamp.
    contactMessage.setSubmissionTs(iEpochTimestamp);

    // Calculate the hash of the contact form through a simple MD5 hash which takes into account all inputs plus time.
    std::string strContactHash = drogon::utils::getMd5(
            rgPostData.at("name") + rgPostData.at("surname") + rgPostData.at("email")
            + rgPostData.at("email") + rgPostData.at("message") + std::to_string(iEpochTimestamp)
    );
    contactMessage.setHash(strContactHash);

    // Insert the record in the database and redirect to it.
    contactMessagesMapper.insert(
            contactMessage,
            [callback](const drogon_model::sqlite3::ContactMessages &model)
            {
                // Take the user to the created log.
                callback(
                        drogon::HttpResponse::newRedirectionResponse(
                                "/contact/messages/view/" + *model.getHash() + '/'
                        )
                );
            },
            [callback](const drogon::orm::DrogonDbException &exception)
            {
                // Take the user back to the contact form and log the error.
                callback(drogon::HttpResponse::newRedirectionResponse("/contact/"));
                LOG_ERROR << exception.base().what();
            }
    );
}
