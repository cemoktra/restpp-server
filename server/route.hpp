#pragma once

#include <memory>
#include <functional>
#include <vector>

namespace restpp {
  class request;
  class response;
  class routenode;

  class route {
    public:
      enum route_match {
        no_match = 0x00,
        param_match = 0x01,
        full_match = 0x11
      };

      static std::shared_ptr<route> create(
        const std::string& route, 
        std::function<void(std::shared_ptr<request>, std::shared_ptr<response>)> callback = nullptr
      );

      route_match match(std::shared_ptr<route> other);

      void execute(std::shared_ptr<request> req, std::shared_ptr<response> res);
      
    private:
      route(
        const std::string& route, 
        std::function<void(std::shared_ptr<request>, std::shared_ptr<response>)> callback = nullptr
      );

      std::function<void(std::shared_ptr<request>, std::shared_ptr<response>)> m_callback;
      std::vector<std::shared_ptr<routenode>> m_route;
  };
}