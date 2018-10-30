project(z1amt)

find_package(Boost REQUIRED)

set(SOURCE_FILES z1amt_lib.cpp mat22.cpp mat33.cpp mat33.h PekSolver.cpp PekSolver.h d1node.h)

add_library(z1amt STATIC ${SOURCE_FILES})
