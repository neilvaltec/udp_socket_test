cmake_minimum_required(VERSION 3.10)

project(SocketExample)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(send send.cpp)
add_executable(receive receive.cpp)

# If any of the libraries like 'pthread' or others are required, link them as follows
# target_link_libraries(udp_client <library_name>)
# target_link_libraries(udp_server <library_name>)
