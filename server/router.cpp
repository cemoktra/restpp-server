#include "router.hpp"
#include "routetree.hpp"
#include "types.hpp"
#include "request.hpp"
#include "response.hpp"
#include "route.hpp"
#include "utils.hpp"

#include <iostream>


namespace restpp {
  router::router()
    : m_root(routetree::create())
  {
  }

  void router::get(const std::string& route, route_callback callback)
  {
    auto route_obj = route::create(request_method::GET, route, callback);
    // TODO: remove duplicat code
    m_root->add(route_obj->nodes(), route_obj->callback());
    m_routes.emplace_back(route_obj);
  }

  void router::post(const std::string& route, route_callback callback)
  {
    auto route_obj = route::create(request_method::POST, route, callback);
    // TODO: remove duplicat code
    m_root->add(route_obj->nodes(), route_obj->callback());
    m_routes.emplace_back(route_obj);
  }

  bool router::route_request(std::shared_ptr<request> request, std::shared_ptr<response> response)
  {
    std::shared_ptr<route> full_match;
    std::shared_ptr<route> param_match;

    for (auto route : m_routes) {
      auto result = request->match(route);
      if (!full_match and result == route_match::full_match) {
        full_match = route;
        break;
      }
      else if (!param_match and result == route_match::param_match)
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

  bool router::route_request_tree(std::shared_ptr<request> request, std::shared_ptr<response> response)
  {
    auto [full, param] = m_root->match(request->get_route()->nodes());
    if (full)
      full(request, response, std::nullopt);
    else if (param)
      param(request, response, std::nullopt);
    else
      return false;
    return true;
  }
}