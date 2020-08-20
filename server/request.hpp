#pragma once

#include <string_view>
#include <memory>
#include <queue>
#include <map>


namespace restpp {
  class request {
    public:
      enum Method {
        GET,
        POST
      };

      static std::shared_ptr<request> parse(std::string_view req);

      Method method();

    private:
      request(std::queue<std::string_view> lines);
      void parseRequestLine(std::string_view line);
      void parseHeaders(std::queue<std::string_view>& lines);

      Method m_method;
      std::map<std::string, std::string> m_headers;
  };
}