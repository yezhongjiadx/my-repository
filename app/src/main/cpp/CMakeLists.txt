cmake_minimum_required(VERSION 3.22)
project("guessgame")

find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_ttf REQUIRED CONFIG)

add_library(
        native-lib SHARED
        main.cpp
)

target_link_libraries(
        native-lib
        SDL2::SDL2
        SDL2_ttf::SDL2_ttf
        android
        log
)
