#pragma once

#include <memory>
#include <string>

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

        private:
            response();

            std::string reason(const http_status& status);

            http_status m_status;
            std::string m_text;
    };
} // namespace restpp
