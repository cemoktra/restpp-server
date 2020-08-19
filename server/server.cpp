#include "server.hpp"
#include "request.hpp"
#include "response.hpp"
#include "exceptions.hpp"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <iostream>
#include <stack>
#include <sstream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <exception>


namespace restpp
{
  
  void server::setRouter(std::shared_ptr<interfaces::router_interface> router)
  {
    m_router = router;
  }

  void server::stop()
  {
    std::cout << "stopping server" << std::endl;
    shutdown(m_sock, SHUT_RD);
    close(m_sock);
    m_stop = true;
  }

  std::future<void> server::serve(unsigned int port)
  {
    return std::async(&server::async_serve, this, port);
  }

  void server::async_serve(unsigned int port)
  {
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sock < 0)
        throw restpp_socket_exception(restpp_socket_exception::creation);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &(addr.sin_addr));
    if (bind(m_sock, (struct sockaddr *) &addr, sizeof(addr)))
        throw restpp_socket_exception(restpp_socket_exception::bind);
    if (listen(m_sock, 5))
        throw restpp_socket_exception(restpp_socket_exception::listen);

    std::cout << "listing on port " << port << std::endl;
    while (!m_stop) {
      socklen_t len = sizeof(sockaddr_in);
      sockaddr_in *remote = (sockaddr_in *)malloc(sizeof(sockaddr_in));

      auto remote_sock = accept(m_sock, (struct sockaddr *) remote, &len);
      if (remote_sock < 0)
        throw restpp_socket_exception(restpp_socket_exception::accept);
      m_handledRequests.emplace_back(std::async(&server::handle, this, remote_sock, (void*) remote));
    }

    close(m_sock);
  }

  bool server::handle(int sock, void *addr)
  {
    std::string req;
    char buffer[1024];
    size_t read = 0;

    while ((read = recv(sock, buffer, 1024, 0)))
    {
      std::copy(buffer, buffer + read, std::back_inserter(req));

      int available;
      
      ioctl(sock, FIONREAD, &available);
      if (!available)
        break;
    }

    auto request = request::parse(req);
    auto response = response::create();
    std::cout << "responding " << sock << std::endl;

    if (m_router)
      m_router->route(request, response);
    
    auto response_str = response->toString();
    // std::cout << response_str << std::endl;
    std::vector<char> bytes(response_str.begin(), response_str.end());
    bytes.push_back('\0');
    send(sock, &bytes.front(), bytes.size(), 0);

    free(addr);
    close(sock);
    
    return true;
  }

} // namespace restpp
