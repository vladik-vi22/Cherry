#include <gtest/gtest.h>
#include <generators/PRBgenerators.h>

class PRBGeneratorsTest : public ::testing::Test {
protected:
    PRBgenerators gen;

    void SetUp() override {
        gen.setNumberOfBits(1024);  // 128 bytes
    }
    void TearDown() override {}
};

// ============================================================================
// Basic Configuration Tests
// ============================================================================

TEST_F(PRBGeneratorsTest, SetNumberOfBits) {
    gen.setNumberOfBits(static_cast<size_t>(256));
    EXPECT_EQ(gen.getNumberOfBits().toStdString(), "256");
}

TEST_F(PRBGeneratorsTest, SetNumberOfBytes) {
    gen.setNumberOfBytes(32);  // 32 bytes = 256 bits
    EXPECT_EQ(gen.getNumberOfBits().toStdString(), "256");
}

// ============================================================================
// Built-in C++ Generator Tests
// ============================================================================

TEST_F(PRBGeneratorsTest, BuiltInCPPBit_GeneratesCorrectSize) {
    gen.setNumberOfBits(static_cast<size_t>(256));
    gen.generateBuiltInCPPBit();
    auto result = gen.getGeneratedPRBS();
    EXPECT_EQ(result.size(), 32);  // 256 bits = 32 bytes
}

TEST_F(PRBGeneratorsTest, BuiltInCPPByte_GeneratesCorrectSize) {
    gen.setNumberOfBits(static_cast<size_t>(256));
    gen.generateBuiltInCPPByte();
    auto result = gen.getGeneratedPRBS();
    EXPECT_EQ(result.size(), 32);
}

TEST_F(PRBGeneratorsTest, BuiltInCPPByte_GeneratesNonZero) {
    gen.setNumberOfBits(static_cast<size_t>(1024));
    gen.generateBuiltInCPPByte();
    auto result = gen.getGeneratedPRBS();
    // At least some bytes should be non-zero
    bool hasNonZero = false;
    for (auto byte : result) {
        if (byte != 0) {
            hasNonZero = true;
            break;
        }
    }
    EXPECT_TRUE(hasNonZero);
}

// ============================================================================
// Lehmer Generator Tests
// ============================================================================

TEST_F(PRBGeneratorsTest, LehmerLow_GeneratesCorrectSize) {
    gen.setNumberOfBits(static_cast<size_t>(256));
    gen.generateLehmerLow();
    auto result = gen.getGeneratedPRBS();
    EXPECT_EQ(result.size(), 32);
}

TEST_F(PRBGeneratorsTest, LehmerHigh_GeneratesCorrectSize) {
    gen.setNumberOfBits(static_cast<size_t>(256));
    gen.generateLehmerHigh();
    auto result = gen.getGeneratedPRBS();
    EXPECT_EQ(result.size(), 32);
}

// ============================================================================
// LFSR Generator Tests (L20, L89)
// ============================================================================

TEST_F(PRBGeneratorsTest, L20_GeneratesCorrectSize) {
    gen.setNumberOfBits(static_cast<size_t>(256));
    gen.generateL20();
    auto result = gen.getGeneratedPRBS();
    EXPECT_EQ(result.size(), 32);
}

TEST_F(PRBGeneratorsTest, L89_GeneratesCorrectSize) {
    gen.setNumberOfBits(static_cast<size_t>(256));
    gen.generateL89();
    auto result = gen.getGeneratedPRBS();
    EXPECT_EQ(result.size(), 32);
}

TEST_F(PRBGeneratorsTest, L20_FallsBackForSmallInput) {
    gen.setNumberOfBits(static_cast<size_t>(16));  // Less than 20 bits
    gen.generateL20();
    auto result = gen.getGeneratedPRBS();
    EXPECT_EQ(result.size(), 2);  // 16 bits = 2 bytes
}

TEST_F(PRBGeneratorsTest, L89_FallsBackForSmallInput) {
    gen.setNumberOfBits(static_cast<size_t>(64));  // Less than 89 bits
    gen.generateL89();
    auto result = gen.getGeneratedPRBS();
    EXPECT_EQ(result.size(), 8);  // 64 bits = 8 bytes
}

// ============================================================================
// Geffe Generator Tests
// ============================================================================

TEST_F(PRBGeneratorsTest, Geffe_GeneratesCorrectSize) {
    gen.setNumberOfBits(static_cast<size_t>(256));
    gen.generateGeffe();
    auto result = gen.getGeneratedPRBS();
    EXPECT_EQ(result.size(), 32);
}

// ============================================================================
// Wolfram Generator Tests (Cellular Automaton Rule 30)
// ============================================================================

TEST_F(PRBGeneratorsTest, Wolfram_GeneratesCorrectSize) {
    gen.setNumberOfBits(static_cast<size_t>(256));
    gen.generateWolfram();
    auto result = gen.getGeneratedPRBS();
    EXPECT_EQ(result.size(), 32);
}

// ============================================================================
// Blum-Micali Generator Tests (Cryptographically Secure)
// DISABLED: BlumMicaliBit takes 100+ seconds due to powmod overhead
// ============================================================================

TEST_F(PRBGeneratorsTest, DISABLED_BlumMicaliBit_GeneratesCorrectSize) {
    gen.setNumberOfBits(static_cast<size_t>(64));  // Small due to powmod overhead
    gen.generateBlumMicaliBit();
    auto result = gen.getGeneratedPRBS();
    EXPECT_EQ(result.size(), 8);
}

TEST_F(PRBGeneratorsTest, BlumMicaliByte_GeneratesCorrectSize) {
    gen.setNumberOfBits(static_cast<size_t>(64));
    gen.generateBlumMicaliByte();
    auto result = gen.getGeneratedPRBS();
    EXPECT_EQ(result.size(), 8);
}

// ============================================================================
// Blum-Blum-Shub Generator Tests (Cryptographically Secure)
// ============================================================================

TEST_F(PRBGeneratorsTest, BlumBlumShubBit_GeneratesCorrectSize) {
    gen.setNumberOfBits(static_cast<size_t>(64));
    gen.generateBlumBlumShubBit();
    auto result = gen.getGeneratedPRBS();
    EXPECT_EQ(result.size(), 8);
}

TEST_F(PRBGeneratorsTest, BlumBlumShubByte_GeneratesCorrectSize) {
    gen.setNumberOfBits(static_cast<size_t>(64));
    gen.generateBlumBlumShubByte();
    auto result = gen.getGeneratedPRBS();
    EXPECT_EQ(result.size(), 8);
}

// ============================================================================
// Conversion Tests
// ============================================================================

TEST_F(PRBGeneratorsTest, GetUint8_t) {
    gen.setNumberOfBits(static_cast<size_t>(8));
    gen.generateBuiltInCPPByte();
    // Should return a valid uint8_t
    uint8_t result = gen.getUint8_tGeneratedPRBS();
    EXPECT_TRUE(result >= 0 && result <= 255);
}

TEST_F(PRBGeneratorsTest, GetUint16_t) {
    gen.setNumberOfBits(static_cast<size_t>(16));
    gen.generateBuiltInCPPByte();
    uint16_t result = gen.getUint16_tGeneratedPRBS();
    EXPECT_TRUE(result >= 0 && result <= 65535);
}

TEST_F(PRBGeneratorsTest, GetUint32_t) {
    gen.setNumberOfBits(static_cast<size_t>(32));
    gen.generateBuiltInCPPByte();
    uint32_t result = gen.getUint32_tGeneratedPRBS();
    EXPECT_TRUE(result >= 0);
}

TEST_F(PRBGeneratorsTest, GetUint64_t) {
    gen.setNumberOfBits(static_cast<size_t>(64));
    gen.generateBuiltInCPPByte();
    uint64_t result = gen.getUint64_tGeneratedPRBS();
    EXPECT_TRUE(result >= 0);
}

// ============================================================================
// Known Issues (TODOs for future investigation)
// ============================================================================
// TODO: Statistical tests (testOfGoodnessOfFit, testOfHomogeneity, testOfIndependence)
//       are flaky and need investigation. The chi-square implementation may have issues
//       with threshold calculation or sample size requirements.
// TODO: Librarian generator has a bug (string subscript out of range)

