cmake_minimum_required(VERSION 3.22)
project(libchip-game VERSION 1.0)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS OFF)

# Define the library and its source files
file(GLOB_RECURSE SOURCES "src/*.c")
add_library(libchip-game SHARED "${SOURCES}")

# Include directories
target_include_directories(libchip-game PRIVATE "include")

# Installation rules
install(TARGETS libchip-game DESTINATION "bin")

add_executable(main "test/main.c")
target_link_libraries(main PRIVATE libchip-game)
