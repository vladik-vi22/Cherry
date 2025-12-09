#include <gtest/gtest.h>
#include <rpn/RPNgenerator.h>
#include <bigint/BigInt.hpp>

using namespace bigint;

class RPNGeneratorTest : public ::testing::Test {
protected:
    RPNgenerator gen;
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================================
// Prime Number Generation Tests
// ============================================================================

TEST_F(RPNGeneratorTest, GeneratePrime16Bit) {
    // Generate a 16-bit prime (small, fast)
    BigInt prime = gen.generatePrimeNumber(16);
    // Prime should be positive and non-zero
    EXPECT_TRUE(prime > constants::ZERO);
    EXPECT_TRUE(prime.isPositive());
    // Prime should be odd (except 2)
    EXPECT_TRUE(prime.isOdd() || prime == constants::TWO);
    // Note: The generator doesn't guarantee exact bit length,
    // it generates a prime with UP TO the specified bits
    // Just verify it's a reasonable size (note: typo in API - bitLenght)
    EXPECT_TRUE(prime.bitLenght() <= 16);
}

TEST_F(RPNGeneratorTest, GeneratePrime32Bit) {
    // Generate a 32-bit prime
    BigInt prime = gen.generatePrimeNumber(32);
    EXPECT_TRUE(prime > constants::ZERO);
    EXPECT_TRUE(prime.isOdd());
    // Verify it's within 32-bit range (note: typo in API - bitLenght)
    EXPECT_TRUE(prime.bitLenght() <= 32);
}

TEST_F(RPNGeneratorTest, GeneratedPrimePassesFermatTest) {
    // Generate a prime and verify it passes Fermat's little theorem
    // For prime p and base a coprime to p: a^(p-1) ≡ 1 (mod p)
    BigInt prime = gen.generatePrimeNumber(16);
    BigInt base("2", 10);
    BigInt result = powmod(base, prime - constants::ONE, prime);
    EXPECT_EQ(result.toStdString(10), "1");
}

TEST_F(RPNGeneratorTest, GeneratedPrimePassesFermatTestBase3) {
    // Test with base 3 as well
    BigInt prime = gen.generatePrimeNumber(32);
    BigInt base("3", 10);
    BigInt result = powmod(base, prime - constants::ONE, prime);
    EXPECT_EQ(result.toStdString(10), "1");
}

TEST_F(RPNGeneratorTest, PrimeIsNotDivisibleBySmallPrimes) {
    // Generate a prime and verify it's not divisible by small primes
    BigInt prime = gen.generatePrimeNumber(32);
    std::vector<int> smallPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    for (int p : smallPrimes) {
        BigInt divisor(static_cast<uint32_t>(p));
        BigInt remainder = prime % divisor;
        // Either the prime IS the small prime, or it's not divisible by it
        EXPECT_TRUE(prime == divisor || remainder != constants::ZERO);
    }
}

