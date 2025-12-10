#include <gtest/gtest.h>
#include <crypto/CompactLWE.h>
#include <bigint/BigInt.hpp>

using namespace bigint;

class CompactLWETest : public ::testing::Test {
protected:
    CompactLWE alice;
    CompactLWE bob;

    void SetUp() override {
        alice.generateKeys();
        bob.generateKeys();
    }
};

// Test key generation
TEST_F(CompactLWETest, KeyGenerationWorks) {
    CompactLWE lwe;
    lwe.generateKeys();

    auto params = lwe.getPublicParamethers();
    EXPECT_TRUE(params.q > constants::Zero);
    EXPECT_TRUE(params.t > constants::Zero);
}

// Test public parameters are set
TEST_F(CompactLWETest, PublicParametersAreSet) {
    auto params = alice.getPublicParamethers();

    EXPECT_GT(params.n, 0);
    EXPECT_GT(params.m, 0);
    EXPECT_GT(params.l, 0);
}

// Test public key is generated
TEST_F(CompactLWETest, PublicKeyIsGenerated) {
    auto publicKey = alice.getPublicKey();

    EXPECT_FALSE(publicKey.empty());
}

// TODO: CompactLWE basicEncrypt/basicDecrypt has a bug:
// "vector iterators incompatible" - the decrypt function uses iterators
// from different vectors (ciphertext vs privateKey.s). This needs deeper
// investigation and is out of scope for this commit.

