#pragma once

#include <string_view>
#include <memory>
#include <queue>
#include <map>


namespace restpp {
  class route;

  class request {
    public:
      enum Method {
        GET,
        POST
      };

      static std::shared_ptr<request> parse(std::string_view req);

      Method method();

      std::shared_ptr<route> get_route();

    private:
      request(std::queue<std::string_view> lines);
      void parseRequestLine(std::string_view line);
      void parseHeaders(std::queue<std::string_view>& lines);

      Method m_method;
      std::string m_route_string;
      std::shared_ptr<route> m_route;
      std::map<std::string, std::string> m_headers;
  };
}