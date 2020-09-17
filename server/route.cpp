#include "route.hpp"
#include "routenode.hpp"
#include "utils.hpp"


namespace restpp {
  route::route(
    request_method method,
    const std::string& route, 
    std::function<void(std::shared_ptr<request>, std::shared_ptr<response>, std::optional<std::map<std::string, std::string>> params)> callback
  ) 
  : m_method(method)
  , m_callback(callback)
  {
    std::string_view route_view = route;
    if (route_view[0] == '/')
      route_view = route_view.substr(1);
    auto route_split = utils::split(route_view, "/");

    while (route_split.size()) {
      auto item = route_split.front(); route_split.pop();
      m_route.emplace_back(std::make_shared<routenode>(item));
    }
  }

  std::shared_ptr<route> route::create(
    request_method method,
    const std::string& route_string, 
    std::function<void(std::shared_ptr<request>, std::shared_ptr<response>, std::optional<std::map<std::string, std::string>> params)> callback
  ) {
    auto route_object = new route(method, route_string, callback);
    return std::shared_ptr<route>(route_object);
  }

  route_callback route::callback()
  {
    return m_callback;
  }

  std::vector<std::shared_ptr<routenode>> route::nodes()
  {
    return m_route;
  }
}