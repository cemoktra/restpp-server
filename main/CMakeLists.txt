set(SOURCES
  main.cpp
)

add_executable(restpp_main ${SOURCES})
add_dependencies(restpp_main restpp_server)

target_link_libraries(restpp_main restpp_server pthread)