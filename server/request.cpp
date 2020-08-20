#include "request.hpp"
#include "exceptions.hpp"
#include "utils.hpp"
#include <iostream>
#include <strings.h>

namespace restpp {
  std::shared_ptr<request> request::parse(std::string_view req)
  {
    return std::shared_ptr<request>(new request(utils::split(req, "\n")));
  }

  request::request(std::queue<std::string_view> lines)
  {
    parseRequestLine(lines.front()); lines.pop();
    parseHeaders(lines);
  }

  void request::parseRequestLine(std::string_view line)
  {
    auto request_details = utils::split(line, " ");
    auto method = request_details.front(); request_details.pop();
    auto requestUri = request_details.front(); request_details.pop();
    auto httpVersion = request_details.front(); request_details.pop();

    if (utils::str_compare(method, "get"))
      m_method = request::GET;
    else if (utils::str_compare(method, "post"))
      m_method = request::POST;
    else 
      throw restpp_unsupported_method_exception();
  }

  void request::parseHeaders(std::queue<std::string_view>& lines)
  {
    while (true) {
      auto line = lines.front(); lines.pop();
      if (line.length() <= 1)
        break;
      m_headers.insert(utils::split_keyValue(line));
    }
  }

  request::Method request::method()
  {
    return m_method;
  }
}