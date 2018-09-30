include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

find_package(GTest REQUIRED)

add_executable(runBasicTests
        basic_checks.cpp
        z1amt_test.cpp)

target_link_libraries(runBasicTests gtest gtest_main pthread)
target_link_libraries(runBasicTests z1amt)