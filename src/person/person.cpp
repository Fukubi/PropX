#include "person.h"

namespace person {
std::string Person::getName() { return name; }

std::string Person::getCpf() { return cpf; }

std::string Person::getRg() { return rg; }

std::string Person::getBirthday() { return birthday; }

void Person::setName(std::string name) { this->name = name; }

void Person::setCpf(std::string cpf) { this->cpf = cpf; }

void Person::setRg(std::string rg) { this->rg = rg; }

void Person::setBirthday(std::string birthday) { this->birthday = birthday; }

std::string ClientPJ::getCnpj() { return cnpj; }

void ClientPJ::setCnpj(std::string cnpj) { this->cnpj = cnpj; }

std::string Seller::getOffice() { return this->office; }

void Seller::setOffice(std::string office) { this->office = office; }
} // namespace person
