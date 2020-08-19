#pragma once

#include <exception>

namespace restpp {
  class restpp_unsupported_method_exception : std::exception
  {
  public:
    restpp_unsupported_method_exception() {};
    const char* what() const noexcept override
    {
      return "method not supported";
    }
  };

  class restpp_socket_exception : std::exception
  {
  public:
    enum exception_reason {
      creation,
      bind,
      listen,
      accept
    };

    restpp_socket_exception(exception_reason reason) : m_reason(reason) {};
    
    const char* what() const noexcept override { 
      switch (m_reason)
      {
      case creation:
        return "could not create socket";
      case bind:
        return "could not bind socket";
      case listen:
        return "could not listen on socket";
      case accept:
        return "could not accept socket";
      default:
        return "unknown";
      }
    }
  
  private:
    exception_reason m_reason;
  };
}