#include "cryptography.h"
#include "person.h"
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
  ASSERT_EQ(user->getAuthorization(), user::Authorization::CLIENT);
  ASSERT_EQ(user->getPerson(), nullptr);
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

TEST(UserTest, ShouldBePossibleDifferentAuthorizations) {
  std::unique_ptr<user::User> user =
      std::make_unique<user::User>(user::Authorization::ADMINISTRATOR);

  EXPECT_EQ(user->getAuthorization(), user::Authorization::ADMINISTRATOR);
}

TEST(UserTest, SetPersonDataOfUser) {
  std::unique_ptr<user::User> user = std::make_unique<user::User>();
  std::shared_ptr<person::Person> person = std::make_shared<person::ClientPF>();

  person->setName("John");
  person->setCpf("167.317.040-40");
  person->setRg("31.732.999-6");
  person->setBirthday("01/01/2000");

  user->setPerson(person);

  EXPECT_EQ(user->getPerson()->getName(), "John");
}