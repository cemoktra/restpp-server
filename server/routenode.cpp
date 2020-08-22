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

  bool routenode::param_match(std::shared_ptr<routenode> other)
  {
    return m_type == param or other->m_type == param;
  }

  std::string routenode::name()
  {
    return m_name;
  }
}