#include "server.hpp"
#include "request.hpp"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <iostream>
#include <stack>
#include <sstream>
#include <sys/ioctl.h>
#include <unistd.h>


namespace restpp
{
  void server::addRoute()
  {

  }

  void server::serve(unsigned int port)
  {
    auto sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &(addr.sin_addr));
    bind(sock, (struct sockaddr *) &addr, sizeof(addr));
    listen(sock, 5);
    std::stack<std::thread> threads;

    while (true) {
      socklen_t len = sizeof(sockaddr_in);
      sockaddr_in *remote = (sockaddr_in *)malloc(sizeof(sockaddr_in));

      auto remote_sock = accept(sock, (struct sockaddr *) remote, &len);
      m_handledRequests.emplace_back(std::async(&server::handle, this, remote_sock, (void*) remote));
    }
  }

  bool server::handle(int sock, void *addr)
  {
    std::string req;
    char buffer[1024];
    size_t read = 0;

    while (read = recv(sock, buffer, 1024, 0))
    {
      std::copy(buffer, buffer + read, std::back_inserter(req));

      int available;
      ioctl(sock, FIONREAD, &available);
      if (!available)
        break;
    }

    auto request = request::parse(req);

    free(addr);
    close(sock);
    
    return true;
  }

} // namespace restpp
