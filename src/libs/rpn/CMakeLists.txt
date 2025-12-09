# RPN Generator Library - Reverse Polish Notation parser/calculator

add_library(cherry_rpn STATIC
    src/RPNgenerator.cpp
    include/rpn/RPNgenerator.h
)

add_library(Cherry::RPN ALIAS cherry_rpn)

# Enable AUTOMOC for Q_OBJECT classes
set_target_properties(cherry_rpn PROPERTIES AUTOMOC ON)

target_include_directories(cherry_rpn
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(cherry_rpn
    PUBLIC
        Qt6::Core
        Cherry::BigInt
        Cherry::Generators
    PRIVATE
        cherry_warnings
)

target_compile_features(cherry_rpn PUBLIC cxx_std_20)

