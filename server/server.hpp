#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <vector>
#include <future>

namespace restpp {
  class server {
    public:
      server() = default;
      ~server() = default;

      void addRoute();
      void serve(unsigned int port);

    protected:
      bool handle(int sock, void *addr);

      std::vector<std::future<bool>> m_handledRequests;
  };
}