#pragma once

#include <memory>
#include <string>

namespace restpp
{
    class response {
        public:
            static std::shared_ptr<response> create();

            std::string toString();

        private:
            response();

            int m_status;
            std::string m_reason;
    };
} // namespace restpp
