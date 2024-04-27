#pragma once

#include <memory>
#include <string>

/// @brief Namespace for the supported cryptographies supported
namespace cryptography {
/// @brief The abstract class used by all other cryptographies
class Cryptography {
public:
  /// @brief Empty destructor
  virtual ~Cryptography(){};

  /// @brief Encrypt the text using the cryptographic algorithm
  /// @param text The text to encrypt
  /// @return The encrypted text
  virtual std::string encrypt(std::string text) = 0;

  /// @brief Compare a text with a hash (or encrypted text)
  /// @param hash The hash (or encrypted text) to compare to
  /// @param text The plain text to check
  /// @return True if text generates hash, false otherwise
  virtual bool compare(std::string hash, std::string text) = 0;
};

/// @brief BCrypt encryption, default encryption used for passwords
class BCrypt : public Cryptography {
  /// @brief Encrypt the text using the cryptographic algorithm
  /// @param text The text to encrypt
  /// @return The encrypted text
  virtual std::string encrypt(std::string text);

  /// @brief Compare a text with a hash (or encrypted text)
  /// @param hash The hash (or encrypted text) to compare to
  /// @param text The plain text to check
  /// @return True if text generates hash, false otherwise
  virtual bool compare(std::string hash, std::string text);
};

/// @brief A PlainText encryption, the same as no encryption
class PlainText : public Cryptography {
  /// @brief Encrypt the text using the cryptographic algorithm
  /// @param text The text to encrypt
  /// @return The encrypted text
  virtual std::string encrypt(std::string text);

  /// @brief Compare a text with a hash (or encrypted text)
  /// @param hash The hash (or encrypted text) to compare to
  /// @param text The plain text to check
  /// @return True if text generates hash, false otherwise
  virtual bool compare(std::string hash, std::string text);
};
} // namespace cryptography
