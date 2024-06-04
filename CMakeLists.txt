cmake_minimum_required(VERSION 3.16)
project(sfml_example)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

find_package(SFML 2.6 COMPONENTS graphics REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
include_directories(/usr/local/include)

add_executable(sfml_example src/main.cpp
        src/helper_functions.cpp
        src/helper_functions.h
        src/welcomeWindow.h
        src/welcomWindow.cpp
        src/tile.cpp
        src/tile.h
        src/TextureManager.cpp
        src/TextureManager.h
        src/board.cpp
        src/board.h
        "../Redundant Files/Tests.cpp"
        "../Redundant Files/Tests.h"
        src/leaderboard.cpp
        src/leaderboard.h)
target_link_libraries(sfml_example PRIVATE sfml-graphics sfml-audio)
target_compile_features(sfml_example PRIVATE cxx_std_17)

install(TARGETS sfml_example)