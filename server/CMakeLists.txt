set(SOURCES
  server.cpp
  request.cpp
)

set (HEADERS
  server.hpp
  request.hpp
)

add_library(restpp_server ${SOURCES} ${HEADERS})