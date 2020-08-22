set(SOURCES
  server.cpp
  request.cpp
  response.cpp
  router.cpp
  route.cpp
  routenode.cpp
  utils.cpp
)

set (HEADERS
  interfaces/router.hpp
  server.hpp
  request.hpp
  response.hpp
  router.hpp
  route.hpp
  routenode.hpp
  exceptions.hpp
  utils.hpp
)

add_library(restpp_server ${SOURCES} ${HEADERS})