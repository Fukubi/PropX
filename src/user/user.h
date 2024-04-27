#pragma once

#include "cryptography.h"
#include <memory>
#include <string>

/// @brief User classes and managers
namespace user {
/// @brief The type of Authorization that a can user
enum Authorization { ADMINISTRATOR, SELLER, CLIENT };

/// @brief Represents a User in the application
class User {
public:
  /// @brief Default constructor that initializes everything empty, uses a
  /// PlainText Encryption and has a Client Authorization
  User();

  /// @brief A client with a custom Authorization, all other values are the same
  /// as the default constructor
  /// @param authorization The Authorization level of the user
  User(Authorization authorization);

  /// @brief Get username of User
  /// @return The username
  std::string getUsername();
  /// @brief Get the authorization level of User
  /// @return The authorization level of User
  Authorization getAuthorization();

  /// @brief Set a new username to user
  /// @param username The new username
  void setUsername(std::string username);
  /// @brief Set a password and encrypt it based on current cryptography
  /// @param password The new password to be encrypted and saved
  void setPassword(std::string password);
  /// @brief Set a new type of encryption
  /// @param cryptography The reference to the Cryptography used to encrypt
  void setEncryption(std::unique_ptr<cryptography::Cryptography> cryptography);

  /// @brief Execute login to user comparing the requested password to the user
  /// password
  /// @param password The requested password used to login
  /// @return true if success, otherwise false
  bool login(std::string password);

private:
  /// @brief Username that the user is refered as
  std::string username;
  /// @brief Encrypted password of current user
  std::string password;
  /// @brief The current used cryptography
  std::unique_ptr<cryptography::Cryptography> cryptography;
  /// @brief The authorization level of the user
  Authorization authorization;
};
} // namespace user
