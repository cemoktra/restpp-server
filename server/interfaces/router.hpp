#pragma once

#include <memory>
#include <functional>

namespace restpp {
  class request;
  class response;


  namespace interfaces {
    class router_interface {
      public:
        virtual void get(const std::string& route, std::function<void(std::shared_ptr<request>, std::shared_ptr<response>)> callback) = 0;
        virtual void post(const std::string& route, std::function<void(std::shared_ptr<request>, std::shared_ptr<response>)> callback) = 0;

        virtual bool route_request(std::shared_ptr<request> request, std::shared_ptr<response> response) = 0;
    };
  }
}