cmake_minimum_required(VERSION 3.15)
project(laba1 C)

set(CMAKE_C_STANDARD 99)

add_executable(laba1 main.c utils.c utils.h complex_unit.c complex_unit.h vector.c vector.h interface_vector.c interface_vector.h)