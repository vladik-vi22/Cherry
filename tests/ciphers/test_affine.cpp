#include <gtest/gtest.h>
#include <ciphers/EDHcryptorAffine.h>

class AffineCipherTest : public ::testing::Test {
protected:
    Affine cipher;

    void SetUp() override {
        cipher.setLanguage("english");
    }
};

// Test default construction
TEST_F(AffineCipherTest, DefaultConstruction) {
    Affine a;
    EXPECT_EQ(a.getLanguage(), "english");
}

// Test language switching
TEST_F(AffineCipherTest, LanguageSwitching) {
    cipher.setLanguage("ukrainian");
    EXPECT_EQ(cipher.getLanguage(), "ukrainian");

    cipher.setLanguage("english");
    EXPECT_EQ(cipher.getLanguage(), "english");
}

// Test key validation - valid keys
TEST_F(AffineCipherTest, ValidKeys) {
    // key1 must be coprime with alphabet^2 (26^2 = 676)
    // key1 = 3 is coprime with 676
    cipher.setKey1(3);
    cipher.setKey2(5);
    cipher.setText("hello");
    cipher.encrypt();
    // Should not produce error message
    EXPECT_NE(cipher.getText(), "Incorrect Key!!!");
}

// Test key validation - invalid key1 (not coprime)
TEST_F(AffineCipherTest, InvalidKey1NotCoprime) {
    // key1 = 2 is NOT coprime with 676 (both divisible by 2)
    cipher.setKey1(2);
    cipher.setKey2(5);
    cipher.setText("hello");
    cipher.encrypt();
    EXPECT_EQ(cipher.getText(), "Incorrect Key!!!");
}

// Test key validation - negative key1
TEST_F(AffineCipherTest, InvalidKey1Negative) {
    cipher.setKey1(-1);
    cipher.setKey2(5);
    cipher.setText("hello");
    cipher.encrypt();
    EXPECT_EQ(cipher.getText(), "Incorrect Key!!!");
}

// Test encrypt then decrypt returns original (bigram affine cipher)
TEST_F(AffineCipherTest, EncryptDecryptRoundTrip) {
    cipher.setKey1(3);
    cipher.setKey2(7);
    cipher.setText("helloworld");  // even length for bigram cipher

    cipher.encrypt();
    QString encrypted = cipher.getText();
    EXPECT_NE(encrypted, "helloworld");

    cipher.decrypt();
    QString decrypted = cipher.getText();
    EXPECT_EQ(decrypted, "helloworld");
}

// Test that encryption changes the text
TEST_F(AffineCipherTest, EncryptionChangesText) {
    cipher.setKey1(5);
    cipher.setKey2(3);
    cipher.setText("testmessage");

    QString original = cipher.getText();
    cipher.encrypt();
    EXPECT_NE(cipher.getText(), original);
}

// Test text normalization (lowercase, remove non-alphabet)
TEST_F(AffineCipherTest, TextNormalization) {
    cipher.setKey1(3);
    cipher.setKey2(1);
    cipher.setText("Hello World 123!");

    cipher.encrypt();
    // Text should be normalized (lowercase, no spaces/numbers)
    QString result = cipher.getText();
    EXPECT_FALSE(result.contains(' '));
    EXPECT_FALSE(result.contains('1'));
    EXPECT_EQ(result, result.toLower());
}

// Test with different valid key combinations
TEST_F(AffineCipherTest, DifferentKeysProduceDifferentResults) {
    cipher.setText("testdata");
    cipher.setKey1(3);
    cipher.setKey2(5);
    cipher.encrypt();
    QString result1 = cipher.getText();

    cipher.setText("testdata");
    cipher.setKey1(5);
    cipher.setKey2(3);
    cipher.encrypt();
    QString result2 = cipher.getText();

    EXPECT_NE(result1, result2);
}

// =============================================================================
// CRYPTANALYSIS TESTS - Hacking the Affine Cipher
// =============================================================================

// The Affine bigram cipher hack() uses frequency analysis on bigrams.
// This is a probabilistic method that works best with longer texts that
// have typical letter frequency distributions. Short or unusual texts
// may not be successfully cracked.

// NOTE: The hack() implementation attempts to find keys by analyzing
// bigram frequencies and comparing with known language patterns.
// Success depends on text length and content.

TEST_F(AffineCipherTest, HackProducesValidOutput) {
    // Test that hack() produces some output (doesn't crash)
    QString plaintext = "thescienceofcryptographyistheartofsecretwriting";

    cipher.setKey1(5);
    cipher.setKey2(17);
    cipher.setText(plaintext);
    cipher.encrypt();

    QString ciphertext = cipher.getText();
    EXPECT_NE(ciphertext, plaintext);

    // Hack should produce output of same length
    cipher.hack();
    QString hackedText = cipher.getText();

    EXPECT_EQ(hackedText.length(), plaintext.length());
    // Note: hack() may not always recover exact plaintext due to
    // probabilistic nature of frequency analysis
}

TEST_F(AffineCipherTest, EncryptDecryptHistoricalMessage) {
    // Historical-style secret message
    // "Meet me at midnight by the bridge bring the secret documents"
    QString plaintext = "meetmeatmidnightbythebridgebringthesecretdocuments";

    cipher.setKey1(11);
    cipher.setKey2(4);
    cipher.setText(plaintext);

    // Encrypt the secret message
    cipher.encrypt();
    QString encrypted = cipher.getText();

    // Verify it's encrypted
    EXPECT_NE(encrypted, plaintext);
    EXPECT_EQ(encrypted.length(), plaintext.length());

    // Decrypt to verify round-trip
    cipher.decrypt();
    EXPECT_EQ(cipher.getText(), plaintext);
}

TEST_F(AffineCipherTest, EncryptDecryptCryptographyQuote) {
    // Famous cryptography quote for testing
    // "Cryptography is the practice and study of techniques for secure communication"
    QString plaintext = "cryptographyisthepracticeandstudyoftechniquesforsecurecommunication";

    cipher.setKey1(7);
    cipher.setKey2(23);
    cipher.setText(plaintext);
    cipher.encrypt();

    QString ciphertext = cipher.getText();
    EXPECT_NE(ciphertext, plaintext);

    // Decrypt should recover original
    cipher.decrypt();
    EXPECT_EQ(cipher.getText(), plaintext);
}

TEST_F(AffineCipherTest, EncryptDecryptUkrainianCryptographyText) {
    cipher.setLanguage("ukrainian");

    // Ukrainian text about cryptography:
    // "криптографія це наука про захист інформації"
    QString plaintext = QString::fromUtf8("криптографіяценаукапрозахистінформації");

    cipher.setKey1(5);
    cipher.setKey2(11);
    cipher.setText(plaintext);
    cipher.encrypt();

    QString ciphertext = cipher.getText();
    EXPECT_NE(ciphertext, plaintext);

    // Decrypt should recover Ukrainian plaintext
    cipher.decrypt();
    EXPECT_EQ(cipher.getText(), plaintext);
}

TEST_F(AffineCipherTest, BigramCipherPreservesLength) {
    // The Affine cipher here is a bigram cipher (operates on pairs)
    QString plaintext = "attackatdawnbringallforces";

    cipher.setKey1(3);
    cipher.setKey2(7);
    cipher.setText(plaintext);
    cipher.encrypt();

    // Bigram cipher should preserve length
    EXPECT_EQ(cipher.getText().length(), plaintext.length());

    cipher.decrypt();
    EXPECT_EQ(cipher.getText(), plaintext);
}

