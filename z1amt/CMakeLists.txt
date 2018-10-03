project(z1amt)

set(SOURCE_FILES z1amt_lib.cpp mat22.cpp mat33.cpp mat33.h)

add_library(z1amt STATIC ${SOURCE_FILES})