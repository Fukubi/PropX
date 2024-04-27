#include "cryptography.h"
#include "bcrypt.h"

namespace cryptography {
std::string BCrypt::encrypt(std::string text) {
  return bcrypt::generateHash(text, 12);
}

bool BCrypt::compare(std::string hash, std::string text) {
  return bcrypt::validatePassword(text, hash);
}

std::string PlainText::encrypt(std::string text) { return text; }

bool PlainText::compare(std::string hash, std::string text) {
  return hash == text;
}
} // namespace cryptography
