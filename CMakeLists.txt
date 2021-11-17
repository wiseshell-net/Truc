cmake_minimum_required(VERSION 3.9.2)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(truc)

add_executable(
    truc
    src/games/truc/truc.cpp
    src/games/truc/card.cpp
    src/games/truc/banca.cpp
    src/games/truc/deck.cpp
    src/games/truc/game.cpp
    src/games/truc/human.cpp
    src/games/truc/player.cpp
    src/games/truc/print.cpp
    src/games/truc/statistics.cpp
)
