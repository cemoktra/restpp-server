#include "router.hpp"
#include "request.hpp"
#include "response.hpp"

namespace restpp {
  bool router::route(std::shared_ptr<request> request, std::shared_ptr<response> response)
  {
    return false;
  }
}