#pragma once

#include <memory>


namespace restpp {
  class request;
  class response;


  namespace interfaces {
    class router_interface {
      public:
        virtual bool route(std::shared_ptr<request> request, std::shared_ptr<response> response) = 0;
    };
  }
}