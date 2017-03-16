cmake_minimum_required(VERSION 3.1)

project(path-morphing)

set(CMAKE_CXX_STANDARD 14) # 17 is not supported by cmake 3.7
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FindPkgConfig)
pkg_check_modules(LIB2GEOM REQUIRED 2geom)

find_package(FMT REQUIRED)

set(CATCH_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/catch/" CACHE STRING "Path to Catch header library")

enable_testing()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(geom_helpers)
add_subdirectory(morphing)
add_subdirectory(tests)
add_subdirectory(demos)

install(
    DIRECTORY include/
    DESTINATION include
)
