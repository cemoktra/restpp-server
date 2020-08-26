#pragma once

#include <memory>
#include <string>
#include <map>

namespace restpp
{
    class response {
        public:
            enum http_status {
              OK = 200,
              NOTFOUND = 404,
            };

            static std::shared_ptr<response> create();

            std::string toString();

            void status(const http_status& status);
            void text(const std::string& text);

            void add_header(const std::string& key, const std::string& value);

        private:
            response();

            std::string reason(const http_status& status);

            http_status m_status;
            std::string m_text;
            std::map<std::string, std::string> m_headers;
    };
} // namespace restpp
