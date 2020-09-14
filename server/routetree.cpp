#include "routetree.hpp"
#include "routenode.hpp"
#include <future>


namespace restpp
{
  routetree::routetree(route_callback callback)
    : m_callback(callback)
  {
  }

  std::shared_ptr<routetree> routetree::create(route_callback callback)
  {
    return std::shared_ptr<routetree>(new routetree(callback));
  }

  void routetree::add(std::vector<std::shared_ptr<routenode>> nodes, route_callback callback)
  {
    auto node = nodes.front();
    nodes.erase(nodes.begin());

    std::string name = node->type() == param ? "*" : node->name();
    if (m_children.find(name) == m_children.end())
      m_children[name] = routetree::create(nodes.size() ? nullptr : callback);

    auto child = m_children[name];
    if (nodes.size())
      child->add(nodes, callback);
  }

  std::pair<route_callback, route_callback> routetree::match(std::vector<std::shared_ptr<routenode>> nodes)
  {
    auto node = nodes.front();
    nodes.erase(nodes.begin());

    auto full_match = std::async([=]() {
      return match_full(nodes);
    });
    auto param_match = std::async([=]() {
      return match_param(nodes);
    });

    return std::make_pair<>(full_match.get(), param_match.get());
  }

  route_callback routetree::match_full(std::vector<std::shared_ptr<routenode>> nodes)
  {
    auto node = nodes.front();
    nodes.erase(nodes.begin());

    auto child = m_children.find(node->name());
    if (child == m_children.end())
      return nullptr;
    if (nodes.size())
      return child->second->match_full(nodes);
    return m_callback;
  }

  route_callback routetree::match_param(std::vector<std::shared_ptr<routenode>> nodes)
  {
    auto node = nodes.front();
    nodes.erase(nodes.begin());

    auto full_child = m_children.find(node->name());
    if (full_child != m_children.end()) {
      if (nodes.size())
        return full_child->second->match_param(nodes);
      return m_callback;
    } else {
      auto param_child = m_children.find("*");
      if (param_child != m_children.end()) {
        if (nodes.size())
          return param_child->second->match_param(nodes);
        return m_callback;
      } else
        return nullptr;
    }
  }
}