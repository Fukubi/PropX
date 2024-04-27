#include "user.h"

namespace user {
User::User()
    : username(""), password(""),
      cryptography(std::make_unique<cryptography::PlainText>()),
      authorization(Authorization::CLIENT) {}

User::User(Authorization authorization) { this->authorization = authorization; }

std::string User::getUsername() { return username; }

Authorization User::getAuthorization() { return this->authorization; }

void User::setUsername(std::string username) { this->username = username; }

void User::setPassword(std::string password) {
  this->password = cryptography->encrypt(password);
}

bool User::login(std::string password) {
  return cryptography->compare(this->password, password);
}

void User::setEncryption(
    std::unique_ptr<cryptography::Cryptography> cryptography) {
  this->cryptography = std::move(cryptography);
}
} // namespace user
