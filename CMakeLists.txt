cmake_minimum_required(VERSION 3.0)

project(SOCKET_COMMUNICATION_CPP)

# set(CMAKE_CXX_FLAGS_DEBUG -g)
set(CMAKE_CXX_COMPILER g++)

# Setup testing
enable_testing()
find_package(GTest REQUIRED)

set (SOC_CLIENT 0)
set (SOC_SERVER 1)

set (SOCKET_COM ${SOC_CLIENT})
set (SOURCE_CLIENT main.cpp client.cpp socket_common.cpp)
add_executable(client ${SOURCE_CLIENT})
target_compile_definitions(client PRIVATE -DSOCKET_COM=${SOCKET_COM})
target_link_libraries(client GTest::GTest GTest::Main)

set (SOCKET_COM ${SOC_SERVER})
set (SOURCE_SERVER main.cpp server.cpp socket_common.cpp)
add_executable(server ${SOURCE_SERVER})
target_compile_definitions(server PRIVATE -DSOCKET_COM=${SOCKET_COM})
target_link_libraries(server GTest::GTest GTest::Main)
