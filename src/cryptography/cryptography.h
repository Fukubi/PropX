#pragma once

#include <memory>
#include <string>

namespace cryptography {
class Cryptography {
public:
  virtual ~Cryptography(){};

  virtual std::string encrypt(std::string text) = 0;

  virtual bool compare(std::string hash, std::string text) = 0;
};

class BCrypt : public Cryptography {
  virtual std::string encrypt(std::string text);

  virtual bool compare(std::string hash, std::string text);
};

class PlainText : public Cryptography {
  virtual std::string encrypt(std::string text);

  virtual bool compare(std::string hash, std::string text);
};
} // namespace cryptography
