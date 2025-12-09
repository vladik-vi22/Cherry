# Cherry Benchmarks
# Note: BigInt benchmarks are in the external bigint-cpp library

# ============================================================================
# Google Benchmark
# ============================================================================

include(FetchContent)

FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.8.3
)

# Disable benchmark tests
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(benchmark)

# ============================================================================
# Cipher Benchmarks
# ============================================================================

add_executable(bench_ciphers
    ciphers/bench_ciphers.cpp
)

target_link_libraries(bench_ciphers PRIVATE
    cherry_ciphers
    benchmark::benchmark
    benchmark::benchmark_main
)

# ============================================================================
# Generator Benchmarks
# ============================================================================

add_executable(bench_generators
    generators/bench_generators.cpp
)

target_link_libraries(bench_generators PRIVATE
    cherry_generators
    benchmark::benchmark
    benchmark::benchmark_main
)

