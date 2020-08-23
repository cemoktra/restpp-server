#include "../server/server.hpp"
#include "../server/router.hpp"
#include "../server/response.hpp"
#include "../server/request.hpp"
#include <chrono>
#include <csignal>
#include <thread>
#include <sstream>

std::atomic<bool> quit(false); 

void signalHandler( int signum ) {
  quit.store(true);
}

void hello(std::shared_ptr<restpp::request> req, std::shared_ptr<restpp::response> res, std::optional<std::map<std::string, std::string>> params)
{
  res->text("world");
  res->status(restpp::response::OK);
}

void hello_name(std::shared_ptr<restpp::request> req, std::shared_ptr<restpp::response> res, std::optional<std::map<std::string, std::string>> params)
{
  std::ostringstream oss;
  auto paramsMap = params.value_or(std::map<std::string, std::string>());
  oss << "Hello " << paramsMap["name"] << "!";
  res->text(oss.str());
  res->status(restpp::response::OK);
}

int main(int argc, char **args)
{
  signal(SIGINT, signalHandler); 

  auto router = std::make_shared<restpp::router>();
  router->get("/hello", hello);
  router->get("/hello/:name", hello_name);

  restpp::server server;
  server.setRouter(router);

  auto result = server.serve(5000);
  while (std::future_status::ready != result.wait_for(std::chrono::seconds(1)))
  {
    std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(500));
    if (quit.load())
      server.stop();
  }
  return 0;
}