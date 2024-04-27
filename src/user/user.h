#pragma once

#include "cryptography.h"
#include <memory>
#include <string>

namespace user {
class User {
public:
  User();

  std::string getUsername();

  void setUsername(std::string username);
  void setPassword(std::string password);
  void setEncryption(std::unique_ptr<cryptography::Cryptography> cryptography);

  bool login(std::string password);

private:
  std::string username;
  std::string password;
  std::unique_ptr<cryptography::Cryptography> cryptography;
};
} // namespace user
