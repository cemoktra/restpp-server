#pragma once

#include <functional>
#include <string>
#include <map>
#include <memory>

namespace restpp {
  class request;
  class response;

  using route_callback = std::function<void(std::shared_ptr<request>, std::shared_ptr<response>, std::optional<std::map<std::string, std::string>> params)>;

  enum nodetype {
    fixed,
    param
  };

  enum request_method {
    GET,
    POST
  };

  enum route_match {
    no_match = 0x00,
    param_match = 0x01,
    full_match = 0x11
  };
}