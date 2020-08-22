#pragma once

#include <string>
#include <memory>


namespace restpp {
  class request;
  class response;

  class routenode {
  public:
    enum nodetype {
      fixed,
      param
    };

    routenode(std::string_view name);

    std::string name();

    bool full_match(std::shared_ptr<routenode> other);
    bool param_match(std::shared_ptr<routenode> other);

  private:
    nodetype m_type;
    std::string m_name;
  };
}