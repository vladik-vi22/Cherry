#include <benchmark/benchmark.h>
#include <generators/PRBgenerators.h>

// ============================================================================
// Built-in C++ Generators
// ============================================================================

static void BM_Generator_BuiltInCPPBit_1KB(benchmark::State& state) {
    PRBgenerators gen;
    gen.setNumberOfBits(8 * 1024);  // 1 KB
    for (auto _ : state) {
        gen.generateBuiltInCPPBit();
        benchmark::DoNotOptimize(gen.getGeneratedPRBS());
    }
}
BENCHMARK(BM_Generator_BuiltInCPPBit_1KB);

static void BM_Generator_BuiltInCPPByte_1KB(benchmark::State& state) {
    PRBgenerators gen;
    gen.setNumberOfBits(8 * 1024);  // 1 KB
    for (auto _ : state) {
        gen.generateBuiltInCPPByte();
        benchmark::DoNotOptimize(gen.getGeneratedPRBS());
    }
}
BENCHMARK(BM_Generator_BuiltInCPPByte_1KB);

// ============================================================================
// Lehmer Generators
// ============================================================================

static void BM_Generator_LehmerLow_1KB(benchmark::State& state) {
    PRBgenerators gen;
    gen.setNumberOfBits(8 * 1024);
    for (auto _ : state) {
        gen.generateLehmerLow();
        benchmark::DoNotOptimize(gen.getGeneratedPRBS());
    }
}
BENCHMARK(BM_Generator_LehmerLow_1KB);

static void BM_Generator_LehmerHigh_1KB(benchmark::State& state) {
    PRBgenerators gen;
    gen.setNumberOfBits(8 * 1024);
    for (auto _ : state) {
        gen.generateLehmerHigh();
        benchmark::DoNotOptimize(gen.getGeneratedPRBS());
    }
}
BENCHMARK(BM_Generator_LehmerHigh_1KB);

// ============================================================================
// LFSR Generators (L20, L89)
// ============================================================================

static void BM_Generator_L20_1KB(benchmark::State& state) {
    PRBgenerators gen;
    gen.setNumberOfBits(8 * 1024);
    for (auto _ : state) {
        gen.generateL20();
        benchmark::DoNotOptimize(gen.getGeneratedPRBS());
    }
}
BENCHMARK(BM_Generator_L20_1KB);

static void BM_Generator_L89_1KB(benchmark::State& state) {
    PRBgenerators gen;
    gen.setNumberOfBits(8 * 1024);
    for (auto _ : state) {
        gen.generateL89();
        benchmark::DoNotOptimize(gen.getGeneratedPRBS());
    }
}
BENCHMARK(BM_Generator_L89_1KB);

// ============================================================================
// Geffe Generator
// ============================================================================

static void BM_Generator_Geffe_1KB(benchmark::State& state) {
    PRBgenerators gen;
    gen.setNumberOfBits(8 * 1024);
    for (auto _ : state) {
        gen.generateGeffe();
        benchmark::DoNotOptimize(gen.getGeneratedPRBS());
    }
}
BENCHMARK(BM_Generator_Geffe_1KB);

// ============================================================================
// Wolfram Generator (Cellular Automaton Rule 30)
// ============================================================================

static void BM_Generator_Wolfram_1KB(benchmark::State& state) {
    PRBgenerators gen;
    gen.setNumberOfBits(8 * 1024);
    for (auto _ : state) {
        gen.generateWolfram();
        benchmark::DoNotOptimize(gen.getGeneratedPRBS());
    }
}
BENCHMARK(BM_Generator_Wolfram_1KB);

// ============================================================================
// Blum-Micali Generator (Cryptographically Secure - SLOW)
// ============================================================================

static void BM_Generator_BlumMicaliBit_64bits(benchmark::State& state) {
    PRBgenerators gen;
    gen.setNumberOfBits(64);  // Small due to powmod overhead
    for (auto _ : state) {
        gen.generateBlumMicaliBit();
        benchmark::DoNotOptimize(gen.getGeneratedPRBS());
    }
}
BENCHMARK(BM_Generator_BlumMicaliBit_64bits);

static void BM_Generator_BlumMicaliByte_64bits(benchmark::State& state) {
    PRBgenerators gen;
    gen.setNumberOfBits(64);
    for (auto _ : state) {
        gen.generateBlumMicaliByte();
        benchmark::DoNotOptimize(gen.getGeneratedPRBS());
    }
}
BENCHMARK(BM_Generator_BlumMicaliByte_64bits);

// ============================================================================
// Blum-Blum-Shub Generator (Cryptographically Secure - SLOW)
// ============================================================================

static void BM_Generator_BlumBlumShubBit_64bits(benchmark::State& state) {
    PRBgenerators gen;
    gen.setNumberOfBits(64);
    for (auto _ : state) {
        gen.generateBlumBlumShubBit();
        benchmark::DoNotOptimize(gen.getGeneratedPRBS());
    }
}
BENCHMARK(BM_Generator_BlumBlumShubBit_64bits);

static void BM_Generator_BlumBlumShubByte_64bits(benchmark::State& state) {
    PRBgenerators gen;
    gen.setNumberOfBits(64);
    for (auto _ : state) {
        gen.generateBlumBlumShubByte();
        benchmark::DoNotOptimize(gen.getGeneratedPRBS());
    }
}
BENCHMARK(BM_Generator_BlumBlumShubByte_64bits);


