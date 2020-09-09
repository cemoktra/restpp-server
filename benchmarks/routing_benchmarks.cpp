#include <benchmark/benchmark.h>
#include "../server/router.hpp"
#include "../server/request.hpp"
#include <list>
#include <numeric>
#include <sstream>


static std::shared_ptr<restpp::router> create_router()
{
    std::list<int> route_chars(26);
    std::iota(route_chars.begin(), route_chars.end(), (int) 'a');

    auto router = std::make_shared<restpp::router>();

    for (auto part_1 : route_chars) {
        for (auto part_2 : route_chars) {
            std::ostringstream oss;
            oss << "/" << (char) part_1 << "/" << (char) part_2;

            router->get(oss.str(), nullptr);
        }
    }

    return router;
}

static void BM_Routing(benchmark::State& state, const std::string& route) {
    // Perform setup here
    auto router = create_router();
    auto request_str = "GET " + route + " HTTP/1.1\n\n";
    auto request = restpp::request::parse(request_str);

    for (auto _ : state) {
        router->route_request(request, nullptr);
    }
    state.SetItemsProcessed(state.iterations());
}


BENCHMARK_CAPTURE(BM_Routing, "route_aa", "/a/a");
BENCHMARK_CAPTURE(BM_Routing, "route_mn", "/m/n");
BENCHMARK_CAPTURE(BM_Routing, "route_zz", "/z/z");
