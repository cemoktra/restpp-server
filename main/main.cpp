#include "../server/server.hpp"
#include "../server/router.hpp"
#include <chrono>
#include <csignal>
#include <thread>


std::atomic<bool> quit(false); 

void signalHandler( int signum ) {
  quit.store(true);
}

int main(int argc, char **args)
{
  signal(SIGINT, signalHandler); 

  auto router = std::make_shared<restpp::router>();

  restpp::server server;
  auto result = server.serve(5000);
  while (std::future_status::ready != result.wait_for(std::chrono::seconds(1)))
  {
    std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(500));
    if (quit.load())
      server.stop();
  }
  return 0;
}