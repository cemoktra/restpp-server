#include "request.hpp"
#include "route.hpp"
#include "utils.hpp"
#include "exceptions.hpp"
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

  route_match request::match(std::shared_ptr<route> other_route)
  {
    if (!m_route)
      m_route = route::create(m_method, m_route_string);
    return other_route->match(m_route);
  }
  
  void request::parseRequestLine(std::string_view line)
  {
    auto request_details = utils::split(line, " ");
    auto method = request_details.front(); request_details.pop();
    m_route_string = request_details.front(); request_details.pop();
    auto httpVersion = request_details.front(); request_details.pop();

    if (utils::str_compare(method, "get"))
      m_method = request_method::GET;
    else if (utils::str_compare(method, "post"))
      m_method = request_method::POST;
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

  request_method request::method()
  {
    return m_method;
  }
}