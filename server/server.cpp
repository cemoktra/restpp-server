#include "server.hpp"
#include "request.hpp"
#include "response.hpp"
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
  class restpp_exception : std::exception
  {
      public:
        restpp_exception(const std::string& msg) : message(msg) {}
        const char* what() const noexcept override { return message.c_str(); }

      private:
        std::string message;
  };

  void server::addRoute()
  {

  }

  void server::serve(unsigned int port)
  {
    auto sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        throw restpp_exception("Cannot create socket");
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &(addr.sin_addr));
    if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)))
        throw restpp_exception("Cannot bin socket");
    if (listen(sock, 5))
        throw restpp_exception("Cannot listen socket");
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
    
    auto response_str = response->toString();
    std::cout << response_str << std::endl;
    std::vector<char> bytes(response_str.begin(), response_str.end());
    bytes.push_back('\0');
    send(sock, &bytes.front(), bytes.size(), 0);

    free(addr);
    close(sock);
    
    return true;
  }

} // namespace restpp
