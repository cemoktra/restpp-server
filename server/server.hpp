#pragma once

#include "interfaces/router.hpp"

#include <sys/socket.h>
#include <sys/types.h>
#include <vector>
#include <future>


namespace restpp {
  class server {
    public:
      server() = default;
      ~server() = default;

      void setRouter(std::shared_ptr<interfaces::router_interface> router);

      std::future<void> serve(unsigned int port);
      void stop();

    protected:
      void async_serve(unsigned int port);
      bool handle(int sock, void *addr);

      std::shared_ptr<interfaces::router_interface> m_router;
      std::vector<std::future<bool>> m_handledRequests;
      int m_sock = -1;
      bool m_stop = false;
  };
}