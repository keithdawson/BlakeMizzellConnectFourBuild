cmake_minimum_required(VERSION 3.13)
project(BlakeMizzellConnectFourBuild C)

set(CMAKE_C_STANDARD 99)

add_executable(BlakeMizzellConnectFourBuild connect4.c connect4.h menu.c game.c)