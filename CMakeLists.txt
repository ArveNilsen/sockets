cmake_minimum_required(VERSION 4.3.2)

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

project(sockets
    LANGUAGES CXX
    VERSION 0.0.1
)

include(cmake/PreventInSourceBuilds.cmake)
include(cmake/ProjectSettings.cmake)
include(cmake/ProjectWarnings.cmake)
include(cmake/ProjectOptions.cmake)

add_subdirectory(src)

option(BUILD_TESTS "Build test targets" ON)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
