cmake_minimum_required(VERSION 3.7)

set(PROJECT_NAME zt-trade-cpp)
include_directories(curl/include)
include_directories(rapidjson)

link_directories(curl/lib ${WORK_HOME}/lib)


find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(${CMAKE_SOURCE_DIR}/src SRCS)
aux_source_directory(${CMAKE_SOURCE_DIR}/rapidjson RJSON)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} libcurl_imp)