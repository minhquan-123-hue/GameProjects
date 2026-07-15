cmake_minimum_required(VERSION 3.16)
project(Breakout2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/exe")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")

find_package(SDL2 REQUIRED)

# Try to locate SDL2_image, SDL2_ttf, and SDL2_mixer using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2TTF REQUIRED SDL2_ttf)
pkg_check_modules(SDL2MIXER REQUIRED SDL2_mixer)

add_executable(breakout2
    src/main.cpp
    src/game.cpp

    # Systems
    src/systems/sdl_manager.cpp
    src/systems/font_manager.cpp
    src/systems/graphic_manager.cpp
    src/systems/sound_manager.cpp

    # States
    src/states/statemachine.cpp
    src/states/menu.cpp
    src/states/playstate.cpp

    # Entities
    src/entities/paddle.cpp
)

target_include_directories(breakout2 PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_include_directories(breakout2 PRIVATE ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})
target_compile_definitions(breakout2 PRIVATE BREAKOUT2_ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets")
target_link_libraries(breakout2 PRIVATE SDL2::SDL2 ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})
