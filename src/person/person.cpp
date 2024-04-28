#include "person.h"

namespace person {
Person::Person() : id(0) {}

Person::Person(long id) : id(id) {}

std::string Person::getName() { return name; }

std::string Person::getCpf() { return cpf; }

std::string Person::getRg() { return rg; }

std::string Person::getBirthday() { return birthday; }

long Person::getId() { return this->id; }

void Person::setName(std::string name) { this->name = name; }

void Person::setCpf(std::string cpf) { this->cpf = cpf; }

void Person::setRg(std::string rg) { this->rg = rg; }

void Person::setBirthday(std::string birthday) { this->birthday = birthday; }

ClientPF::ClientPF() : Person() {}

ClientPF::ClientPF(long id) : Person(id) {}

ClientPJ::ClientPJ() : Person() {}

ClientPJ::ClientPJ(long id) : Person(id) {}

std::string ClientPJ::getCnpj() { return cnpj; }

void ClientPJ::setCnpj(std::string cnpj) { this->cnpj = cnpj; }

Seller::Seller() : Person() {}

Seller::Seller(long id) : Person(id) {}

std::string Seller::getOffice() { return this->office; }

void Seller::setOffice(std::string office) { this->office = office; }
} // namespace person
