cmake_minimum_required (VERSION 2.6)

project (Truc)
include_directories(src)

add_executable(Truc src/utils/Utils.cpp src/Menu.cpp Main.cpp)
