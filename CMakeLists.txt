cmake_minimum_required(VERSION 3.10.2)
project(Workshop_Network_ex1 C)

set(CMAKE_C_STANDARD 11)

add_executable(client client.c)
add_executable(server server.c)
