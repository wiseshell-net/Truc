cmake_minimum_required (VERSION 2.6)

project (WiseShell)
include_directories(src)

add_executable(WiseShell src/utils/Utils.cpp src/Menu.cpp Main.cpp)
