cmake_minimum_required(VERSION 3.21)

project(Cherry
    VERSION 2.0.0
    DESCRIPTION "Cryptography toolkit with BigInt library, ciphers, and cryptosystems"
    LANGUAGES CXX
)

# ============================================================================
# Global Settings
# ============================================================================

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Export compile commands for IDE support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ============================================================================
# Options
# ============================================================================

option(CHERRY_BUILD_TESTS "Build unit tests" ON)
option(CHERRY_BUILD_BENCHMARKS "Build performance benchmarks" ON)
option(CHERRY_BUILD_DOCS "Build documentation" OFF)

# ============================================================================
# Dependencies
# ============================================================================

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Qml
    Quick
    Widgets
)

qt_standard_project_setup()

# Set Qt policies
qt_policy(SET QTP0001 NEW)

# ============================================================================
# External Libraries (via FetchContent)
# ============================================================================

include(FetchContent)

# bigint-cpp - Arbitrary precision integer library
# For local development, use the sibling directory
# For production, use GIT_REPOSITORY with your repo URL
FetchContent_Declare(
    bigint-cpp
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../bigint-cpp
    # GIT_REPOSITORY https://github.com/vladik-vi22/bigint-cpp.git
    # GIT_TAG main
)

FetchContent_MakeAvailable(bigint-cpp)

# ============================================================================
# Compiler Warnings
# ============================================================================

add_library(cherry_warnings INTERFACE)

if(MSVC)
    target_compile_options(cherry_warnings INTERFACE
        /W4
        /permissive-
    )
else()
    target_compile_options(cherry_warnings INTERFACE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wconversion
        -Wsign-conversion
    )
endif()

# ============================================================================
# Libraries
# ============================================================================

add_subdirectory(src/libs/bigint)
add_subdirectory(src/libs/generators)
add_subdirectory(src/libs/rpn)
add_subdirectory(src/libs/ciphers)
add_subdirectory(src/libs/crypto)

# ============================================================================
# Main Application
# ============================================================================

add_subdirectory(src/app)

# ============================================================================
# Tests
# ============================================================================

if(CHERRY_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# ============================================================================
# Benchmarks
# ============================================================================

if(CHERRY_BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

# ============================================================================
# Installation
# ============================================================================

include(GNUInstallDirs)

install(TARGETS Cherry
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

