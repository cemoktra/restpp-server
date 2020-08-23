#pragma once

#include "types.hpp"
#include <string>
#include <memory>
#include <optional>


namespace restpp {
  class request;
  class response;

  class routenode {
  public:
    routenode(std::string_view name);

    std::string name();

    bool full_match(std::shared_ptr<routenode> other);
    std::optional<std::pair<std::string, std::string>> param_match(std::shared_ptr<routenode> other);

  private:
    nodetype m_type;
    std::string m_name;
  };
}