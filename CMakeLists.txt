cmake_minimum_required(VERSION 3.22)
project(libchip-game VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS OFF)

# Define the library and its source files
file(GLOB_RECURSE SOURCES "src/*.c")
add_library(libchip-game SHARED "${SOURCES}")
target_include_directories(libchip-game PRIVATE "include")

# Automatically export all symbols if using MSVC
if(MSVC)
    set_target_properties(libchip-game PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

# Installation rules
install(TARGETS libchip-game DESTINATION "bin")

# Temporary test
add_executable(main "test/main.c")
target_link_libraries(main PRIVATE libchip-game)
target_include_directories(main PRIVATE "include")
