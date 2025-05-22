cmake_minimum_required(VERSION 3.28)
project(MyGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(MyGame main.cpp)
set_property(TARGET MyGame PROPERTY CXX_STANDARD 17)
target_compile_features(MyGame PRIVATE cxx_std_17)
target_link_libraries(MyGame 
    PRIVATE 
    SFML::Graphics
    SFML::Audio
    SFML::Network
    SFML::Window
    SFML::System
    )