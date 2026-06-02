cmake_minimum_required(VERSION 3.10)

project(flappybird)

set(CMAKE_CXX_STANDARD 17)

# Include header folders
include_directories(include)

# Find SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Put executable into finalprogram/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_SOURCE_DIR}/finalprogram)

# Source files
set(SOURCES
    src/main.cpp
    src/game.cpp
    src/entities/background.cpp
    src/entities/ground.cpp
    src/entities/bird.cpp
    src/entities/pipe.cpp
    src/entities/pipepair.cpp
    src/states/StateMachine.cpp
    src/states/MenuState.cpp
    src/systems/imagemanager.cpp
    src/systems/sdlmanager.cpp
    src/systems/FontManager.cpp
    
)

# Create executable
add_executable(flappy ${SOURCES})

# Link libraries
target_link_libraries(flappy
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
)