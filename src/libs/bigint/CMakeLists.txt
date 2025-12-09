# BigInt Library - Qt/QML bridge for bigint-cpp
# Core BigInt functionality is provided by external bigint-cpp library

# Cherry::BigInt provides Qt/QML integration (BigIntCalculator)
add_library(cherry_bigint STATIC
    src/BigIntCalculator.cpp
    include/bigint/BigIntCalculator.h
)

set_target_properties(cherry_bigint PROPERTIES AUTOMOC ON)

add_library(Cherry::BigInt ALIAS cherry_bigint)

target_include_directories(cherry_bigint
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(cherry_bigint
    PUBLIC
        Qt6::Core
        Qt6::Quick
        bigint::bigint  # External bigint-cpp library
    PRIVATE
        cherry_warnings
)

target_compile_features(cherry_bigint PUBLIC cxx_std_20)

