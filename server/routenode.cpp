#include "routenode.hpp"
#include "response.hpp"
#include "request.hpp"


namespace restpp {
  routenode::routenode(std::string_view name)
    : m_name(name)
  {
    if (m_name[0] == ':')
      m_type = param;
    else
      m_type = fixed;
  }

  bool routenode::full_match(std::shared_ptr<routenode> other)
  {
    if (m_type == param or other->m_type == param)
      return false;
    return m_name == other->m_name;
  }

  std::optional<std::pair<std::string, std::string>> routenode::param_match(std::shared_ptr<routenode> other)
  {
    if (m_type == param and other->m_type == fixed)
      return std::make_pair(m_name.substr(1), other->name());
    else
      return std::nullopt;
  }

  std::string routenode::name()
  {
    return m_name;
  }
}