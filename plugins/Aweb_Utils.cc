#include "Aweb_Utils.h"

using namespace drogon;
using namespace Aweb;

void Utils::initAndStart(const Json::Value &config)
{
}

void Utils::shutdown()
{
}

std::string Utils::htmlSpecialChars(const std::string &src)
{
    std::string strBuf;
    strBuf.reserve(src.size());
    for (const char &c : src)
    {
        switch (c)
        {
            case '&':
                strBuf += "&amp;";
                break;
            case '"':
                strBuf += "&quot;";
                break;
            case '\'':
                strBuf += "&apos;";
                break;
            case '<':
                strBuf += "&lt;";
                break;
            case '>':
                strBuf += "&gt";
                break;
            default:
                strBuf += c;
                break;
        }
    }

    return strBuf;
}
