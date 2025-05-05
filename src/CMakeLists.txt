cmake_minimum_required(VERSION 4.0.0)
project(TicTacToe CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(/utf-8)

add_executable(TicTacToe main.cpp game-logic.cpp ai.cpp ui.cpp)

