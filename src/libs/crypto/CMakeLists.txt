# Cryptosystems Library - RSA and Compact-LWE implementations

add_library(cherry_crypto STATIC
    src/RSAcryptosystem.cpp
    src/CompactLWE.cpp
    include/crypto/RSAcryptosystem.h
    include/crypto/CompactLWE.h
)

add_library(Cherry::Crypto ALIAS cherry_crypto)

# Enable AUTOMOC for Q_OBJECT classes
set_target_properties(cherry_crypto PROPERTIES AUTOMOC ON)

target_include_directories(cherry_crypto
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(cherry_crypto
    PUBLIC
        Qt6::Core
        Qt6::Quick
        Cherry::BigInt
        Cherry::RPN
    PRIVATE
        cherry_warnings
)

target_compile_features(cherry_crypto PUBLIC cxx_std_20)

