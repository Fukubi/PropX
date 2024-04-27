#include "cryptography.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

TEST(CryptographyTest, ShouldEncryptPlainText) {
  std::unique_ptr<cryptography::Cryptography> cryptography =
      std::make_unique<cryptography::PlainText>();

  ASSERT_EQ(cryptography->encrypt("passwd"), "passwd");
}

TEST(CryptographyTest, ShouldEncryptBCrypt) {
  std::unique_ptr<cryptography::Cryptography> cryptography =
      std::make_unique<cryptography::BCrypt>();

  EXPECT_THAT(cryptography->encrypt("passwd"), testing::StartsWith("$2b$12$"));
}

TEST(CryptographyTest, ShouldCompareBCrypt) {
  std::unique_ptr<cryptography::Cryptography> cryptography =
      std::make_unique<cryptography::BCrypt>();

  std::string correctPassword = "passwd";
  std::string wrongPassword = "passwe";

  ASSERT_TRUE(cryptography->compare(cryptography->encrypt(correctPassword),
                                    correctPassword));
  ASSERT_FALSE(cryptography->compare(cryptography->encrypt(correctPassword),
                                     wrongPassword));
}

TEST(CryptographyTest, ShouldComparePlainText) {
  std::unique_ptr<cryptography::Cryptography> cryptography =
      std::make_unique<cryptography::PlainText>();

  std::string correctPassword = "passwd";
  std::string wrongPassword = "passwe";

  ASSERT_TRUE(cryptography->compare(cryptography->encrypt(correctPassword),
                                    correctPassword));
  ASSERT_FALSE(cryptography->compare(cryptography->encrypt(correctPassword),
                                     wrongPassword));
}