cmake_minimum_required(VERSION 3.0.0)
project(FINAL_V2 VERSION 0.1.0)


set(MTM_FLAGS_DEBUG "-std=c++11 --pedantic-errors -Wall -g -Werror")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")

set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})

add_executable(FINAL_V2 main.cpp Exceptions.h Graph.h Graph.cpp Gcalc.h Gcalc.cpp Parser.h Parser.cpp gw.h gw.cpp)
