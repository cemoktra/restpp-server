add_executable(bench main.cpp request_benchmarks.cpp routing_benchmarks.cpp)
target_link_libraries(bench benchmark::benchmark restpp_server)