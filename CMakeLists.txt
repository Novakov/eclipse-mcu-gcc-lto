cmake_minimum_required(VERSION 3.12)

include(toolchain.cmake)

project(ToolchainBug C CXX ASM)


if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
else()
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "" FORCE)
endif()

add_subdirectory(app)
add_subdirectory(libs/emlib)