cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_COMPUTED_DEFAULT "20")
set(BUILD_SHARED_LIBS OFF)

project(RendererTester VERSION 0.0.1 DESCRIPTION "A renderer made for me to test things.")

include(FetchContent)

add_subdirectory(Libs)

add_subdirectory(Core)

add_subdirectory(App)
