#include "response.hpp"
#include <sstream>

namespace restpp {
    std::shared_ptr<response> response::create()
    {
        return std::shared_ptr<response>(new response());
    }

    response::response()
        : m_status(NOTFOUND)
    {

    }

    void response::status(const http_status& status)
    {
      m_status = status;
    }

    void response::text(const std::string& text)
    {
      m_text = text;
    }

    std::string response::toString()
    {
        std::ostringstream oss;
        oss << "HTTP/1.1 " << m_status << " " << reason(m_status) << std::endl << std::endl;
        oss << m_text << std::endl;
        return oss.str();
    }

    std::string response::reason(const http_status& status)
    {
      switch (status) {
        case OK:
          return "OK";
        case NOTFOUND:
          return "NOTFOUND";
        default:
          return "UNKNOWN";
      }
    }
}