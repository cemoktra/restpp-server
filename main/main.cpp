#include "../server/server.hpp"

int main(int argc, char **args)
{
  restpp::server server;
  server.serve(5000);
  return 0;
}