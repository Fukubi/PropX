#include "cryptography.h"
#include "user.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>

class MockCryptography : public cryptography::Cryptography {
public:
  MOCK_METHOD(std::string, encrypt, (std::string text), (override));
  MOCK_METHOD(bool, compare, (std::string hash, std::string text), (override));
};

TEST(UserTest, Initialize) {
  std::unique_ptr<user::User> user = std::make_unique<user::User>();

  ASSERT_EQ(user->getUsername(), "");
}

TEST(UserTest, SetsShouldChangeValues) {
  std::unique_ptr<user::User> user = std::make_unique<user::User>();

  user->setUsername("John");

  ASSERT_EQ(user->getUsername(), "John");
}

TEST(UserTest, PasswordShouldEncrypt) {
  std::unique_ptr<user::User> user = std::make_unique<user::User>();
  std::unique_ptr<MockCryptography> cryptography =
      std::make_unique<MockCryptography>();
  EXPECT_CALL(*cryptography, encrypt).Times(testing::Exactly(1));

  user->setEncryption(std::move(cryptography));

  user->setPassword("passw");
}

TEST(UserTest, ShouldLoginWithCorrectPassword) {
  std::unique_ptr<user::User> user = std::make_unique<user::User>();

  user->setEncryption(std::make_unique<cryptography::BCrypt>());
  user->setPassword("passwd");

  EXPECT_TRUE(user->login("passwd"));
  EXPECT_FALSE(user->login("passwe"));
}