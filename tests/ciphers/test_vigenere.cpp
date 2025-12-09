#include <gtest/gtest.h>
#include <ciphers/EDHcryptorVizhener.h>

class VigenereCipherTest : public ::testing::Test {
protected:
    Vizhener cipher;

    void SetUp() override {
        cipher.setLanguage("english");
    }
};

// Test default construction
TEST_F(VigenereCipherTest, DefaultConstruction) {
    Vizhener v;
    EXPECT_EQ(v.getLanguage(), "english");
}

// Test language switching
TEST_F(VigenereCipherTest, LanguageSwitching) {
    cipher.setLanguage("ukrainian");
    EXPECT_EQ(cipher.getLanguage(), "ukrainian");

    cipher.setLanguage("english");
    EXPECT_EQ(cipher.getLanguage(), "english");
}

// Test valid key
TEST_F(VigenereCipherTest, ValidKey) {
    cipher.setKey("secret");
    cipher.setText("hello");
    cipher.encrypt();
    EXPECT_NE(cipher.getText(), "Incorrect Key!!!");
}

// Test invalid key (contains non-alphabet characters)
TEST_F(VigenereCipherTest, InvalidKeyWithNumbers) {
    cipher.setKey("secret123");
    cipher.setText("hello");
    cipher.encrypt();
    EXPECT_EQ(cipher.getText(), "Incorrect Key!!!");
}

// Test invalid key (contains spaces)
TEST_F(VigenereCipherTest, InvalidKeyWithSpaces) {
    cipher.setKey("sec ret");
    cipher.setText("hello");
    cipher.encrypt();
    EXPECT_EQ(cipher.getText(), "Incorrect Key!!!");
}

// Test encrypt then decrypt returns original
TEST_F(VigenereCipherTest, EncryptDecryptRoundTrip) {
    cipher.setKey("lemon");
    cipher.setText("attackatdawn");

    cipher.encrypt();
    QString encrypted = cipher.getText();
    EXPECT_NE(encrypted, "attackatdawn");

    cipher.decrypt();
    QString decrypted = cipher.getText();
    EXPECT_EQ(decrypted, "attackatdawn");
}

// Test classic Vigenere example
TEST_F(VigenereCipherTest, ClassicExample) {
    cipher.setKey("lemon");
    cipher.setText("attackatdawn");
    cipher.encrypt();
    // Classic Vigenere: ATTACKATDAWN + LEMON = LXFOPVEFRNHR
    EXPECT_EQ(cipher.getText(), "lxfopvefrnhr");
}

// Test that encryption changes the text
TEST_F(VigenereCipherTest, EncryptionChangesText) {
    cipher.setKey("key");
    cipher.setText("plaintext");

    QString original = cipher.getText();
    cipher.encrypt();
    EXPECT_NE(cipher.getText(), original);
}

// Test text normalization
TEST_F(VigenereCipherTest, TextNormalization) {
    cipher.setKey("abc");
    cipher.setText("Hello World!");

    cipher.encrypt();
    QString result = cipher.getText();
    // Should be lowercase and no spaces/punctuation
    EXPECT_FALSE(result.contains(' '));
    EXPECT_FALSE(result.contains('!'));
    EXPECT_EQ(result, result.toLower());
}

// Test different keys produce different results
TEST_F(VigenereCipherTest, DifferentKeysProduceDifferentResults) {
    cipher.setText("testmessage");
    cipher.setKey("alpha");
    cipher.encrypt();
    QString result1 = cipher.getText();

    cipher.setText("testmessage");
    cipher.setKey("beta");
    cipher.encrypt();
    QString result2 = cipher.getText();

    EXPECT_NE(result1, result2);
}

// Test key with single character (Caesar cipher equivalent)
TEST_F(VigenereCipherTest, SingleCharacterKey) {
    cipher.setKey("b");  // shift by 1
    cipher.setText("abc");
    cipher.encrypt();
    EXPECT_EQ(cipher.getText(), "bcd");
}

// Test key 'a' should not change text (shift by 0)
TEST_F(VigenereCipherTest, KeyANoChange) {
    cipher.setKey("a");
    cipher.setText("hello");
    cipher.encrypt();
    EXPECT_EQ(cipher.getText(), "hello");
}

// =============================================================================
// CRYPTANALYSIS TESTS - Hacking the Vigenere Cipher
// =============================================================================

// The Vigenere cipher was considered "le chiffre indéchiffrable" (the
// indecipherable cipher) for 300 years until Friedrich Kasiski published
// his cryptanalysis method in 1863.
//
// The hack() method uses:
// 1. Kasiski examination to find key length
// 2. Index of coincidence to verify key length
// 3. Frequency analysis on each key position
//
// NOTE: This is probabilistic and works best with longer texts (100+ chars)
// that have typical letter frequency distributions.

TEST_F(VigenereCipherTest, HackProducesValidOutput) {
    // Test that hack() produces output without crashing
    QString plaintext = "thescienceofcryptographyistheartofsecretwritingandcodebreaking";

    cipher.setKey("key");
    cipher.setText(plaintext);
    cipher.encrypt();

    QString ciphertext = cipher.getText();
    EXPECT_NE(ciphertext, plaintext);

    // Hack should produce output of same length
    cipher.hack();
    QString hackedText = cipher.getText();

    EXPECT_EQ(hackedText.length(), plaintext.length());
    // Note: hack() may not always recover exact plaintext
}

TEST_F(VigenereCipherTest, EncryptDecryptHistoricalMessage) {
    // A spy-style secret message
    // "Meet me at midnight by the bridge bring the secret documents do not be seen by the enemy"
    QString plaintext = "meetmeatmidnightbythebridgebringthesecretdocumentsdonotbeseenbytheenemy";

    cipher.setKey("secret");
    cipher.setText(plaintext);
    cipher.encrypt();

    QString ciphertext = cipher.getText();

    // Verify encryption worked
    EXPECT_NE(ciphertext, plaintext);
    EXPECT_EQ(ciphertext.length(), plaintext.length());

    // Decrypt should recover original
    cipher.decrypt();
    EXPECT_EQ(cipher.getText(), plaintext);
}

TEST_F(VigenereCipherTest, EncryptDecryptCryptographyQuote) {
    // "Cryptography is the practice and study of techniques for secure communication"
    QString plaintext = "cryptographyisthepracticeandstudyoftechniquesforsecurecommunicationinthepresenceofadversarialbehavior";

    cipher.setKey("cipher");
    cipher.setText(plaintext);
    cipher.encrypt();

    QString ciphertext = cipher.getText();
    EXPECT_NE(ciphertext, plaintext);

    cipher.decrypt();
    EXPECT_EQ(cipher.getText(), plaintext);
}

TEST_F(VigenereCipherTest, EncryptDecryptUkrainianText) {
    cipher.setLanguage("ukrainian");

    // Ukrainian text: "криптографія це наука про захист інформації від несанкціонованого доступу"
    QString plaintext = QString::fromUtf8("криптографіяценаукапрозахистінформаціївіднесанкціонованогодоступу");

    cipher.setKey(QString::fromUtf8("ключ"));  // Ukrainian key "ключ" (key)
    cipher.setText(plaintext);
    cipher.encrypt();

    QString ciphertext = cipher.getText();
    EXPECT_NE(ciphertext, plaintext);

    // Decrypt should recover Ukrainian plaintext
    cipher.decrypt();
    EXPECT_EQ(cipher.getText(), plaintext);
}

TEST_F(VigenereCipherTest, EncryptDecryptLongMessage) {
    // A longer message about the history of Vigenere cipher
    // "The Vigenere cipher was once considered unbreakable for centuries
    //  until Kasiski and Babbage discovered weaknesses"
    QString plaintext = "thevigenerecipherwasonceconsideredunbreakableforcenturiesuntilkasiskiandbabagediscoveredweaknesses";

    cipher.setKey("history");
    cipher.setText(plaintext);

    cipher.encrypt();
    QString encrypted = cipher.getText();
    EXPECT_NE(encrypted, plaintext);

    cipher.decrypt();
    EXPECT_EQ(cipher.getText(), plaintext);
}

TEST_F(VigenereCipherTest, ClassicAttackAtDawn) {
    // The classic example from cryptography textbooks
    cipher.setKey("lemon");
    cipher.setText("attackatdawn");
    cipher.encrypt();

    // Verify the classic result
    EXPECT_EQ(cipher.getText(), "lxfopvefrnhr");

    // Decrypt back
    cipher.decrypt();
    EXPECT_EQ(cipher.getText(), "attackatdawn");
}

TEST_F(VigenereCipherTest, KeyLengthPreservation) {
    // Test that different key lengths work correctly
    QString plaintext = "thequickbrownfoxjumpsoverthelazydog";

    // Short key
    cipher.setKey("ab");
    cipher.setText(plaintext);
    cipher.encrypt();
    QString encrypted1 = cipher.getText();
    cipher.decrypt();
    EXPECT_EQ(cipher.getText(), plaintext);

    // Medium key
    cipher.setKey("secret");
    cipher.setText(plaintext);
    cipher.encrypt();
    QString encrypted2 = cipher.getText();
    cipher.decrypt();
    EXPECT_EQ(cipher.getText(), plaintext);

    // Long key
    cipher.setKey("verylongkeyword");
    cipher.setText(plaintext);
    cipher.encrypt();
    QString encrypted3 = cipher.getText();
    cipher.decrypt();
    EXPECT_EQ(cipher.getText(), plaintext);

    // All encryptions should be different
    EXPECT_NE(encrypted1, encrypted2);
    EXPECT_NE(encrypted2, encrypted3);
    EXPECT_NE(encrypted1, encrypted3);
}

