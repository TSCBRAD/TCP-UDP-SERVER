cmake_minimum_required(VERSION 3.20)

project(tcpMonkey LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(tcpMonkey src/main.cpp src/log.cpp)

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(tcpMonkey PRIVATE nlohmann_json::nlohmann_json)

