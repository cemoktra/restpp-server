#include "route.hpp"
#include "routenode.hpp"
#include "utils.hpp"

namespace restpp {
  route::route(
    const std::string& route, 
    std::function<void(std::shared_ptr<request>, std::shared_ptr<response>)> callback
  ) 
  : m_callback(callback)
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
    const std::string& route_string, 
    std::function<void(std::shared_ptr<request>, std::shared_ptr<response>)> callback
  ) {
    auto route_object = new route(route_string, callback);
    return std::shared_ptr<route>(route_object);
  }

  route::route_match route::match(std::shared_ptr<route> other)
  {
    int result = full_match;

    if (m_route.size() != other->m_route.size())
      return no_match;

    auto it_this = m_route.begin();
    auto it_other = other->m_route.begin();

    while (it_this != m_route.end()) {
      if ((*it_this)->full_match(*it_other))
        result &= (int) full_match;
      else if ((*it_this)->param_match(*it_other))
        result &= (int) param_match;
      else
        return no_match;
      
      it_this++;
      it_other++;
    }

    return (route::route_match) result;
  }

  void route::execute(std::shared_ptr<request> req, std::shared_ptr<response> res)
  {
    if (m_callback)
      m_callback(req, res);
  }
}