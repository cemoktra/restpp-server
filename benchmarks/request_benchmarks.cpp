#include <benchmark/benchmark.h>
#include "../server/request.hpp"

static void BM_RequestParsing(benchmark::State& state) {
  std::string request = 
    "POST /cgi-bin/process.cgi HTTP/1.1\n"
    "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\n"
    "Host: www.tutorialspoint.com\n"
    "Content-Type: application/x-www-form-urlencoded\n"
    "Content-Length: length\n"
    "Accept-Language: en-us\n"
    "Accept-Encoding: gzip, deflate\n"
    "Connection: Keep-Alive\n"
    "\n"
    "licenseID=string&content=string&/paramsXML=string\n";

  // Perform setup here
  for (auto _ : state) {
    auto req = restpp::request::parse(request);
  }
  state.SetItemsProcessed(state.iterations());
}


BENCHMARK(BM_RequestParsing);

