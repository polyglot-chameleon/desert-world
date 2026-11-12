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

include(CTest)

if(BUILD_TESTING)
    find_package(Catch2 3 REQUIRED)

    add_executable(game_tests
        test/world_test.cpp
	test/player_test.cpp
        test/cactus_test.cpp

        game/world.cpp
	game/player.cpp
	game/cactus.cpp
    )

    target_include_directories(game_tests
        PRIVATE
            game
    )

    target_link_libraries(game_tests
        PRIVATE
            SDL3::SDL3
            Catch2::Catch2WithMain
    )

    include(Catch)
    catch_discover_tests(game_tests)
endif()
