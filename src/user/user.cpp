#include "user.h"

namespace user {
User::User()
    : username(""), password(""),
      cryptography(std::make_unique<cryptography::PlainText>()),
      authorization(Authorization::CLIENT), id(0) {}

User::User(long id)
    : username(""), password(""),
      cryptography(std::make_unique<cryptography::PlainText>()),
      authorization(Authorization::CLIENT), id(id) {}

User::User(Authorization authorization)
    : username(""), password(""),
      cryptography(std::make_unique<cryptography::PlainText>()),
      authorization(authorization), id(0) {}

User::User(Authorization authorization, long id)
    : username(""), password(""),
      cryptography(std::make_unique<cryptography::PlainText>()),
      authorization(authorization), id(id) {}

std::string User::getUsername() { return username; }

Authorization User::getAuthorization() { return this->authorization; }

std::shared_ptr<person::Person> User::getPerson() { return this->person; }

long User::getId() { return this->id; }

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
void User::setPerson(std::shared_ptr<person::Person> person) {
  this->person = person;
}
} // namespace user
