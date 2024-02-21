cmake_minimum_required(VERSION 3.22)
project(libchip-game VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/utf-8 /W4 /WX)
    add_compile_options("$<$<CONFIG:Release>:/O2>")
    add_compile_options("$<$<CONFIG:Debug>:/Zi>")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(CMAKE_SHARED_LIBRARY_PREFIX "lib")
else ()
    add_compile_options(-Wall -Wextra -Werror)
    add_compile_options("$<$<CONFIG:Release>:-O3>")
    add_compile_options("$<$<CONFIG:Debug>:-g>")
endif ()

# Define the library and its source files
file(GLOB_RECURSE SOURCES "src/*.c")
add_library(chip_game SHARED "${SOURCES}")
target_include_directories(chip_game PRIVATE "include")

# Installation rules
install(TARGETS libchip_game DESTINATION "bin")

# Temporary test
add_executable(main "test/main.c")
target_link_libraries(main PRIVATE chip_game)
target_include_directories(main PRIVATE "include")
