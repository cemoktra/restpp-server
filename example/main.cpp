#include "../server/server.hpp"
#include "../server/router.hpp"
#include "../server/response.hpp"
#include "../server/request.hpp"
#include <chrono>
#include <csignal>
#include <thread>
#include <sstream>
#include <iostream>


std::atomic<bool> quit(false); 

void signalHandler( int signum ) {
  quit.store(true);
}


class my_backend {
  public:
    void hello(std::shared_ptr<restpp::request> req, std::shared_ptr<restpp::response> res, std::optional<std::map<std::string, std::string>> params)
    {
      res->text("{\"message\": \"hello world!\"}");
      res->add_header("content-type", "application/json");
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

    void get_value(std::shared_ptr<restpp::request> req, std::shared_ptr<restpp::response> res, std::optional<std::map<std::string, std::string>> params)
    {
      std::cout << "get_value: " << value << std::endl;
      res->text(value);
      res->status(restpp::response::OK);
    }

    void post_value(std::shared_ptr<restpp::request> req, std::shared_ptr<restpp::response> res, std::optional<std::map<std::string, std::string>> params)
    {
      std::cout << "post_value: " << req->text() << std::endl;
      value = req->text();
      res->status(restpp::response::OK);
    }

  private:
    std::string value;
};

int main(int argc, char **args)
{
  signal(SIGINT, signalHandler); 

  my_backend backend;

  using namespace std::placeholders;
  auto router = std::make_shared<restpp::router>();
  router->get("/hello", 
    std::bind(&my_backend::hello, &backend, _1, _2, _3));
  router->get("/hello/:name", 
    std::bind(&my_backend::hello_name, &backend, _1, _2, _3));
  router->get("/value", 
    std::bind(&my_backend::get_value, &backend, _1, _2, _3));
  router->post("/value", 
    std::bind(&my_backend::post_value, &backend, _1, _2, _3));

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