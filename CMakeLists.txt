cmake_minimum_required(VERSION 3.20)
project(slotmachine)

set(CMAKE_CXX_STANDARD 20)

add_executable(slotmachine src/main.cpp src/random.hpp src/console.hpp src/game.cpp src/game.hpp)

target_include_directories(slotmachine PRIVATE vendor/inireader)
