#pragma once

#include "../types.hpp"

namespace restpp {
  class request;
  class response;

  namespace interfaces {
    class router_interface {
      public:
        virtual void get(const std::string& route, route_callback callback) = 0;
        virtual void post(const std::string& route, route_callback callback) = 0;

        virtual bool route_request(std::shared_ptr<request> request, std::shared_ptr<response> response) = 0;
    };
  }
}