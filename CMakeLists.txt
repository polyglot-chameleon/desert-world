cmake_minimum_required(VERSION 3.20)

project(desert_game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED CONFIG COMPONENTS SDL3)

add_executable(desert
    src/main.cpp
    src/app.cpp

    game/player.cpp
    game/world.cpp
    game/cactus.cpp

    include/app.hpp
    game/player.hpp
    game/world.hpp
    game/cactus.hpp
)

target_include_directories(desert
    PRIVATE
        include
        game
)

target_link_libraries(desert
    PRIVATE
        SDL3::SDL3
)
