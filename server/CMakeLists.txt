set(SOURCES
  server.cpp
  request.cpp
  response.cpp
)

set (HEADERS
  server.hpp
  request.hpp
  response.hpp
)

add_library(restpp_server ${SOURCES} ${HEADERS})