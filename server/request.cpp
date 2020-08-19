#include "request.hpp"
#include "exceptions.hpp"
#include <iostream>
#include <strings.h>

namespace restpp {
  std::shared_ptr<request> request::parse(std::string_view req)
  {
    return std::shared_ptr<request>(new request(request::split(req, "\n")));
  }

  request::request(std::queue<std::string_view> lines)
  {
    parseRequestLine(lines.front()); lines.pop();
    parseHeaders(lines);
  }

  void request::parseRequestLine(std::string_view line)
  {
    auto request_details = request::split(line, " ");
    auto method = request_details.front(); request_details.pop();
    auto requestUri = request_details.front(); request_details.pop();
    auto httpVersion = request_details.front(); request_details.pop();

    if (request::str_compare(method, "get"))
      m_method = request::GET;
    else if (request::str_compare(method, "post"))
      m_method = request::POST;
    else 
      throw restpp_unsupported_method_exception();
  }

  void request::parseHeaders(std::queue<std::string_view> lines)
  {
    while (true) {
      auto line = lines.front(); lines.pop();
      if (line.length() <= 1)
        break;
      m_headers.insert(split_keyValue(line));
    }
  }

  request::Method request::method()
  {
    return m_method;
  }

  std::queue<std::string_view> request::split(std::string_view str, std::string_view delim)
  {
    std::queue<std::string_view> output;
    size_t lastPos = 0;

    while (lastPos < str.size())
    {
        const auto pos = str.find_first_of(delim, lastPos);

        if (lastPos != pos)
            output.push(str.substr(lastPos, pos - lastPos));

        if (pos == std::string_view::npos)
            break;

        lastPos = pos + 1;
    }

    return output;
  }

  std::pair<std::string, std::string> request::split_keyValue(std::string_view str)
  {
    const auto pos = str.find_first_of(": ", 0);

    return std::make_pair<>(
      std::string(str.substr(0, pos)),
      std::string(str.substr(pos + 2))
    );
  }

  bool request::str_compare(std::string_view str1, std::string_view str2)
  {
    // return true;
    return ((str1.size() == str2.size()) && 
      std::equal(str1.begin(), str1.end(), str2.begin(), 
      [] (const char c1, const char c2) {
        return (c1 == c2 || std::toupper(c1) == std::toupper(c2));
      })
    );
  }
}