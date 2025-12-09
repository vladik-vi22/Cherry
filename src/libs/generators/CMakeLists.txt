# PRB Generators Library - Pseudo-random bit generators

add_library(cherry_generators STATIC
    src/PRBgenerators.cpp
    include/generators/PRBgenerators.h
)

set_target_properties(cherry_generators PROPERTIES AUTOMOC ON)

add_library(Cherry::Generators ALIAS cherry_generators)

target_include_directories(cherry_generators
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(cherry_generators
    PUBLIC
        Qt6::Core
        Cherry::BigInt
    PRIVATE
        cherry_warnings
)

target_compile_features(cherry_generators PUBLIC cxx_std_20)

