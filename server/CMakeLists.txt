set(SOURCES
  server.cpp
  request.cpp
  response.cpp
  router.cpp
  utils.cpp
)

set (HEADERS
  interfaces/router.hpp
  server.hpp
  request.hpp
  response.hpp
  router.hpp
  exceptions.hpp
  utils.hpp
)

add_library(restpp_server ${SOURCES} ${HEADERS})