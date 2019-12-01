cmake_minimum_required(VERSION 3.7)

set(PROJECT_NAME zt-trade-cpp)

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(${CMAKE_SOURCE_DIR}/src SRCS)

add_executable(${PROJECT_NAME} ${SRCS})