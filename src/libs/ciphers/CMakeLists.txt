# Ciphers Library - Classical cipher implementations (Vigenère, Affine)

add_library(cherry_ciphers STATIC
    src/EDHcryptorAffine.cpp
    src/EDHcryptorVizhener.cpp
    include/ciphers/EDHcryptorAffine.h
    include/ciphers/EDHcryptorVizhener.h
)

set_target_properties(cherry_ciphers PROPERTIES AUTOMOC ON)

add_library(Cherry::Ciphers ALIAS cherry_ciphers)

target_include_directories(cherry_ciphers
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(cherry_ciphers
    PUBLIC
        Qt6::Core
        Qt6::Quick
    PRIVATE
        cherry_warnings
)

target_compile_features(cherry_ciphers PUBLIC cxx_std_20)

