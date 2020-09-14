#pragma once

#include "types.hpp"
#include <memory>
#include <map>

namespace restpp
{
  class routenode;

  class routetree
  {
    public:
      static std::shared_ptr<routetree> create(route_callback callback = nullptr);

      void add(std::vector<std::shared_ptr<routenode>> nodes, route_callback callback);

      std::pair<route_callback, route_callback> match(std::vector<std::shared_ptr<routenode>> nodes);

    private:
      routetree(route_callback callback = nullptr);

      route_callback match_full(std::vector<std::shared_ptr<routenode>> nodes);
      route_callback match_param(std::vector<std::shared_ptr<routenode>> nodes);

      std::map<std::string, std::shared_ptr<routetree>> m_children;
      route_callback m_callback;
  };
} // namespace restpp
