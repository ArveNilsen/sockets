list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/catch2/3.7.1/lib/cmake")
find_package(Catch2 3 REQUIRED)

include(CTest)
include(Catch)

add_executable(tests
  tests.cpp
  test_RawSocket.cpp
  test_SocketFactory.cpp
)

catch_discover_tests(tests)

target_include_directories(tests PRIVATE ../src/)
target_link_libraries(tests 
    PRIVATE 
        Catch2::Catch2WithMain
        sockets::project_warnings
        sockets::project_options
)
