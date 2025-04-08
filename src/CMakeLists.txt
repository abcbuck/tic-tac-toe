cmake_minimum_required(VERSION 4.0.0)
project(TicTacToe CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(TicTacToe main.cpp game-logic.cpp ai.cpp ui.cpp)

