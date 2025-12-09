# Cherry Tests

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)

# ============================================================================
# BigInt Tests
# ============================================================================

add_executable(test_bigint
    bigint/test_bigint_basic.cpp
    bigint/test_bigint_arithmetic.cpp
    bigint/test_bigint_bitwise.cpp
)

target_link_libraries(test_bigint
    PRIVATE
        GTest::gtest_main
        GTest::gmock
        Cherry::BigInt
)

gtest_discover_tests(test_bigint)

# ============================================================================
# Generators Tests
# ============================================================================

add_executable(test_generators
    generators/test_prb_generators.cpp
)

target_link_libraries(test_generators
    PRIVATE
        GTest::gtest_main
        Cherry::Generators
)

gtest_discover_tests(test_generators)

# ============================================================================
# Ciphers Tests
# ============================================================================

add_executable(test_ciphers
    ciphers/test_affine.cpp
    ciphers/test_vigenere.cpp
)

target_link_libraries(test_ciphers
    PRIVATE
        GTest::gtest_main
        Cherry::Ciphers
)

gtest_discover_tests(test_ciphers)

# ============================================================================
# Crypto Tests
# ============================================================================

add_executable(test_crypto
    crypto/test_rsa.cpp
    crypto/test_compact_lwe.cpp
)

target_link_libraries(test_crypto
    PRIVATE
        GTest::gtest_main
        Cherry::Crypto
)

gtest_discover_tests(test_crypto)

# ============================================================================
# RPN Tests
# ============================================================================

add_executable(test_rpn
    rpn/test_rpn_generator.cpp
)

target_link_libraries(test_rpn
    PRIVATE
        GTest::gtest_main
        Cherry::RPN
)

gtest_discover_tests(test_rpn)

