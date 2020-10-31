cmake_minimum_required(VERSION 3.17)
project(ProveEksamen C)

set(CMAKE_C_STANDARD 90)

add_executable(ProveEksamen obj/main.c include/main.h obj/database.c include/database.h input.c include/input.h inputParser.c include/inputParser.h)