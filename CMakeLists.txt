cmake_minimum_required(VERSION 3.22)
project(GuessGame CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

file(GLOB SOURCES "app/src/main/cpp/*.cpp")

add_library(game SHARED ${SOURCES})

target_link_libraries(game SDL2::SDL2 SDL2_ttf::SDL2_ttf android log)
