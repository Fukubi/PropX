#pragma once

#include <string>

/// @brief Namespace which represent a Person
namespace person {
/// @brief A base class for a Person with basic information
class Person {
public:
  /// @brief Get the name of the person
  /// @return The name of the person
  std::string getName();
  /// @brief Get the CPF of the person
  /// @return The CPF of the person
  std::string getCpf();
  /// @brief Get the RG of the person
  /// @return The RG of the person
  std::string getRg();
  /// @brief Get the birthday of the person (DD/MM/YYYY)
  /// @return The birthday of the person (DD/MM/YYYY)
  std::string getBirthday();

  /// @brief Set the name of the person
  /// @param name The name of the person
  void setName(std::string name);
  /// @brief Set the CPF of the person
  /// @param cpf The CPF of the person
  void setCpf(std::string cpf);
  /// @brief Set the RG of the person
  /// @param rg The RG of the person
  void setRg(std::string rg);
  /// @brief Set the birthday of the person (DD/MM/YYYY)
  /// @param birthday The birthday of the person (DD/MM/YYYY)
  void setBirthday(std::string birthday);

private:
  /// @brief Name of the person
  std::string name;
  /// @brief CPF of the person
  std::string cpf;
  /// @brief RG of the person
  std::string rg;
  /// @brief Birthday of the person (DD/MM/YYYY)
  std::string birthday;
};

/// @brief The Class that represents a Client of type PF
class ClientPF : public Person {};

/// @brief The Class that represents a Client of type PJ
class ClientPJ : public Person {
public:
  /// @brief Get the CNPJ of the Client
  /// @return the CNPJ of the client
  std::string getCnpj();

  /// @brief Set the CNPJ of the Client
  /// @param cnpj The CNPJ of the Client
  void setCnpj(std::string cnpj);

private:
  /// @brief The CNPJ of the client
  std::string cnpj;
};

/// @brief The Class that represents a Seller
class Seller : public Person {
public:
  /// @brief Get the Office name that the seller works
  /// @return The office name that the Seller works
  std::string getOffice();

  /// @brief Set the Office name that the seller works
  /// @param office The name of the Office
  void setOffice(std::string office);

private:
  /// @brief The name of the office that the seller works
  std::string office;
};
} // namespace person
