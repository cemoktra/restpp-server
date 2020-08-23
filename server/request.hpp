#pragma once

#include "types.hpp"
#include <string_view>
#include <memory>
#include <queue>
#include <map>


namespace restpp {
  class route;

  class request {
    public:
      static std::shared_ptr<request> parse(std::string_view req);

      request_method method();

      std::shared_ptr<route> get_route();

    private:
      request(std::queue<std::string_view> lines);
      void parseRequestLine(std::string_view line);
      void parseHeaders(std::queue<std::string_view>& lines);

      request_method m_method;
      std::string m_route_string;
      std::shared_ptr<route> m_route;
      std::map<std::string, std::string> m_headers;
  };
}