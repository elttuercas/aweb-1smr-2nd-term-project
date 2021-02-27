#pragma once

#include <drogon/plugins/Plugin.h>
#include <cmath>

namespace Aweb
{

    class Utils : public drogon::Plugin<Utils>
    {
    public:
        Utils() = default;

        /**
         * Method is called by the framework to initialise and start the plugin.
         * @param config
         */
        void initAndStart(const Json::Value &config) override;
        /**
         * Method is called by the framework to shutdown the plugin.
         */
        void shutdown() override;
        /**
         * Encode a string to make it HTML-safe. Based on https://www.php.net/manual/en/function.htmlspecialchars.
         * Implementation based on https://stackoverflow.com/a/5665377.
         * @return
         */
        std::string htmlSpecialChars(const std::string &);
    };

}
