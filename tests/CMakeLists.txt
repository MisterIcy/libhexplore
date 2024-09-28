message(STATUS "Configuring tests")

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/0953a17a4281fc26831da647ad3fcd5e21e6473b.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set (TEST_SOURCES
    io/IO.gtest.cpp
)

add_executable(tests ${TEST_SOURCES})

target_include_directories(
    tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(
    tests
    PRIVATE
    hexplore
    GTest::gtest_main
    GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(tests)