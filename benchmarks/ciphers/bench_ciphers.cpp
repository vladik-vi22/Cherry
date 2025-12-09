#include <benchmark/benchmark.h>
#include <ciphers/EDHcryptorAffine.h>
#include <ciphers/EDHcryptorVizhener.h>

// ============================================================================
// Affine Cipher Benchmarks
// ============================================================================

static void BM_Affine_Encrypt_Short(benchmark::State& state) {
    Affine cipher;
    cipher.setLanguage("english");
    cipher.setKey1(5);
    cipher.setKey2(8);
    cipher.setText("hello world");
    for (auto _ : state) {
        cipher.encrypt();
        benchmark::DoNotOptimize(cipher.getText());
    }
}
BENCHMARK(BM_Affine_Encrypt_Short);

static void BM_Affine_Encrypt_Medium(benchmark::State& state) {
    Affine cipher;
    cipher.setLanguage("english");
    cipher.setKey1(5);
    cipher.setKey2(8);
    cipher.setText("the quick brown fox jumps over the lazy dog and runs away fast");
    for (auto _ : state) {
        cipher.encrypt();
        benchmark::DoNotOptimize(cipher.getText());
    }
}
BENCHMARK(BM_Affine_Encrypt_Medium);

static void BM_Affine_Encrypt_Long(benchmark::State& state) {
    Affine cipher;
    cipher.setLanguage("english");
    cipher.setKey1(5);
    cipher.setKey2(8);
    // Generate a longer text
    QString longText;
    for (int i = 0; i < 100; ++i) {
        longText += "the quick brown fox jumps over the lazy dog ";
    }
    cipher.setText(longText);
    for (auto _ : state) {
        cipher.encrypt();
        benchmark::DoNotOptimize(cipher.getText());
    }
}
BENCHMARK(BM_Affine_Encrypt_Long);

static void BM_Affine_Decrypt_Short(benchmark::State& state) {
    Affine cipher;
    cipher.setLanguage("english");
    cipher.setKey1(5);
    cipher.setKey2(8);
    cipher.setText("rclla oaplx");
    for (auto _ : state) {
        cipher.decrypt();
        benchmark::DoNotOptimize(cipher.getText());
    }
}
BENCHMARK(BM_Affine_Decrypt_Short);

// ============================================================================
// Vigenere Cipher Benchmarks
// ============================================================================

static void BM_Vigenere_Encrypt_Short(benchmark::State& state) {
    Vizhener cipher;
    cipher.setLanguage("english");
    cipher.setKey("lemon");
    cipher.setText("attackatdawn");
    for (auto _ : state) {
        cipher.encrypt();
        benchmark::DoNotOptimize(cipher.getText());
    }
}
BENCHMARK(BM_Vigenere_Encrypt_Short);

static void BM_Vigenere_Encrypt_Medium(benchmark::State& state) {
    Vizhener cipher;
    cipher.setLanguage("english");
    cipher.setKey("secretkey");
    cipher.setText("the quick brown fox jumps over the lazy dog and runs away fast");
    for (auto _ : state) {
        cipher.encrypt();
        benchmark::DoNotOptimize(cipher.getText());
    }
}
BENCHMARK(BM_Vigenere_Encrypt_Medium);

static void BM_Vigenere_Encrypt_Long(benchmark::State& state) {
    Vizhener cipher;
    cipher.setLanguage("english");
    cipher.setKey("verylongsecretkey");
    // Generate a longer text
    QString longText;
    for (int i = 0; i < 100; ++i) {
        longText += "the quick brown fox jumps over the lazy dog ";
    }
    cipher.setText(longText);
    for (auto _ : state) {
        cipher.encrypt();
        benchmark::DoNotOptimize(cipher.getText());
    }
}
BENCHMARK(BM_Vigenere_Encrypt_Long);

static void BM_Vigenere_Decrypt_Short(benchmark::State& state) {
    Vizhener cipher;
    cipher.setLanguage("english");
    cipher.setKey("lemon");
    cipher.setText("lxfopvefrnhr");
    for (auto _ : state) {
        cipher.decrypt();
        benchmark::DoNotOptimize(cipher.getText());
    }
}
BENCHMARK(BM_Vigenere_Decrypt_Short);

// ============================================================================
// Ukrainian Language Benchmarks
// ============================================================================

static void BM_Affine_Encrypt_Ukrainian(benchmark::State& state) {
    Affine cipher;
    cipher.setLanguage("ukrainian");
    cipher.setKey1(5);
    cipher.setKey2(8);
    cipher.setText("привіт світ");
    for (auto _ : state) {
        cipher.encrypt();
        benchmark::DoNotOptimize(cipher.getText());
    }
}
BENCHMARK(BM_Affine_Encrypt_Ukrainian);

static void BM_Vigenere_Encrypt_Ukrainian(benchmark::State& state) {
    Vizhener cipher;
    cipher.setLanguage("ukrainian");
    cipher.setKey("ключ");
    cipher.setText("привіт світ");
    for (auto _ : state) {
        cipher.encrypt();
        benchmark::DoNotOptimize(cipher.getText());
    }
}
BENCHMARK(BM_Vigenere_Encrypt_Ukrainian);

