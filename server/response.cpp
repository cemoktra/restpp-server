#include "response.hpp"
#include <sstream>

namespace restpp {
    std::shared_ptr<response> response::create()
    {
        return std::shared_ptr<response>(new response());
    }

    response::response()
        : m_status(404)
        , m_reason("NOTFOUND")
    {

    }

    std::string response::toString()
    {
        std::ostringstream oss;
        oss << "HTTP/1.1 " << m_status << " " << m_reason << std::endl << std::endl;
        return oss.str();
    }
}