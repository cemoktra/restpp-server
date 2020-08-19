#pragma once

#include "interfaces/router.hpp"

namespace restpp {
  class router : public interfaces::router_interface {
    public:
      bool route(std::shared_ptr<request> request, std::shared_ptr<response> response) override;
  };
}