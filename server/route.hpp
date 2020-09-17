#pragma once

#include "types.hpp"
#include <memory>
#include <functional>
#include <vector>
#include <map>


namespace restpp {
  class request;
  class response;
  class routenode;

  class route {
    public:      
      static std::shared_ptr<route> create(
        request_method method,
        const std::string& route, 
        route_callback callback = nullptr
      );

      route_callback callback();
      std::vector<std::shared_ptr<routenode>> nodes();
      
    private:
      route(
        request_method method,
        const std::string& route, 
        route_callback callback = nullptr
      );

      request_method m_method;
      route_callback m_callback;
      std::vector<std::shared_ptr<routenode>> m_route;
      std::map<std::string, std::string> m_params;
  };
}