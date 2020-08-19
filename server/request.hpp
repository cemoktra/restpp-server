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
      void parseHeaders(std::queue<std::string_view> lines);

      // TODO: move to string util
      // TODO: consider using C++ 20 coroutine generator
      static std::queue<std::string_view> split(std::string_view str, std::string_view delim);
      static std::pair<std::string, std::string> split_keyValue(std::string_view str);
      static bool str_compare(std::string_view str1, std::string_view str2);

      Method m_method;
      std::map<std::string, std::string> m_headers;
  };
}