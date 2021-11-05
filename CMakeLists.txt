cmake_minimum_required(VERSION 3.9.2)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(truc)

add_executable(
    truc
    src/truc.cpp
    src/card.cpp
    src/banca.cpp
    src/deck.cpp
    src/game.cpp
    src/human.cpp
    src/player.cpp
    src/print.cpp
    src/statistics.cpp
)
