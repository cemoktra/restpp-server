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
    std::map<std::string, std::string> params;
    auto [full, param] = m_root->match(request->get_route()->nodes(), params);

    if (full)
      full(request, response, std::nullopt);
    else if (param)
      param(request, response, params);
    else
      return false;
    return true;
  }
}