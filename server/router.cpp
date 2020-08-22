#include "router.hpp"
#include "request.hpp"
#include "response.hpp"
#include "route.hpp"
#include "utils.hpp"


namespace restpp {
  void router::get(const std::string& route, std::function<void(std::shared_ptr<request>, std::shared_ptr<response>)> callback)
  {
    // TODO: add type
    m_routes.emplace_back(route::create(route, callback));
  }

  void router::post(const std::string& route, std::function<void(std::shared_ptr<request>, std::shared_ptr<response>)> callback)
  {

  }

  bool router::route_request(std::shared_ptr<request> request, std::shared_ptr<response> response)
  {
    std::shared_ptr<route> full_match;
    std::shared_ptr<route> param_match;

    for (auto route : m_routes) {
      auto result = route->match(request->get_route());
      if (!full_match and result == route::full_match)
        full_match = route;
      else if (!param_match and result == route::param_match)
        param_match = route;
    }

    if (full_match) {
      full_match->execute(request, response);
      return true;
    }
    else if (param_match) {
      param_match->execute(request, response);
      return true;
    }

    return false;
  }
}