cmake_minimum_required(VERSION 3.20)

# ---- Project metadata -------------------------------------------------------
project(ChessEngine
    VERSION 0.1.0
    LANGUAGES CXX
    DESCRIPTION "A C++ chess engine"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Default build type -----------------------------------------------------
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        Debug Release RelWithDebInfo MinSizeRel)
endif()

# ---- Output directories -----------------------------------------------------
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ---- Compiler options -------------------------------------------------------
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    -Wnon-virtual-dtor
)

# Native tune for the host CPU. Disable with -DCHESS_NATIVE=OFF (CI, generic).
option(CHESS_NATIVE "Tune the binary for the host CPU" ON)
if(CHESS_NATIVE AND (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"
                     OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
    add_compile_options(-march=native)
endif()

# ---- Dependencies -----------------------------------------------------------
include(${CMAKE_SOURCE_DIR}/cmake/Dependencies.cmake)

# ---- Subdirectories ---------------------------------------------------------
add_subdirectory(src)

# Enable tests when requested (-DBUILD_TESTING=ON) and a tester is available.
option(CHESS_BUILD_TESTS "Build the unit tests" OFF)
if(CHESS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
