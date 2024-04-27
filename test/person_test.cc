#include "person.h"
#include <gtest/gtest.h>
#include <memory>

TEST(PersonTest, InitializeClientPF) {
  std::unique_ptr<person::Person> person = std::make_unique<person::ClientPF>();

  ASSERT_EQ(person->getName(), "");
  ASSERT_EQ(person->getCpf(), "");
  ASSERT_EQ(person->getRg(), "");
  ASSERT_EQ(person->getBirthday(), "");
}

TEST(PersonTest, InitializeClientPJ) {
  std::shared_ptr<person::Person> person = std::make_shared<person::ClientPJ>();

  ASSERT_EQ(person->getName(), "");
  ASSERT_EQ(person->getCpf(), "");
  ASSERT_EQ(person->getRg(), "");
  ASSERT_EQ(person->getBirthday(), "");
  ASSERT_EQ(std::static_pointer_cast<person::ClientPJ>(person)->getCnpj(), "");
}

TEST(PersonTest, InitializeSeller) {
  std::shared_ptr<person::Person> person = std::make_shared<person::Seller>();

  ASSERT_EQ(person->getName(), "");
  ASSERT_EQ(person->getCpf(), "");
  ASSERT_EQ(person->getRg(), "");
  ASSERT_EQ(person->getBirthday(), "");
  ASSERT_EQ(std::static_pointer_cast<person::Seller>(person)->getOffice(), "");
}

TEST(PersonTest, SetShouldChangeValuesClientPF) {
  std::unique_ptr<person::Person> person = std::make_unique<person::ClientPJ>();

  person->setName("John");
  person->setCpf("167.317.040-40");
  person->setRg("31.732.999-6");
  person->setBirthday("01/01/2000");

  ASSERT_EQ(person->getName(), "John");
  ASSERT_EQ(person->getCpf(), "167.317.040-40");
  ASSERT_EQ(person->getRg(), "31.732.999-6");
  ASSERT_EQ(person->getBirthday(), "01/01/2000");
}

TEST(PersonTest, SetShouldChangeValuesClientPJ) {
  std::shared_ptr<person::Person> person = std::make_shared<person::ClientPJ>();

  person->setName("John");
  person->setCpf("167.317.040-40");
  person->setRg("31.732.999-6");
  person->setBirthday("01/01/2000");
  std::static_pointer_cast<person::ClientPJ>(person)->setCnpj(
      "89.479.280/0001-76");

  ASSERT_EQ(person->getName(), "John");
  ASSERT_EQ(person->getCpf(), "167.317.040-40");
  ASSERT_EQ(person->getRg(), "31.732.999-6");
  ASSERT_EQ(person->getBirthday(), "01/01/2000");
  ASSERT_EQ(std::static_pointer_cast<person::ClientPJ>(person)->getCnpj(),
            "89.479.280/0001-76");
}

TEST(PersonTest, SetShouldChangeValuesSeller) {
  std::shared_ptr<person::Person> person = std::make_shared<person::Seller>();

  person->setName("John");
  person->setCpf("167.317.040-40");
  person->setRg("31.732.999-6");
  person->setBirthday("01/01/2000");
  std::static_pointer_cast<person::Seller>(person)->setOffice("Joao Pessoa");

  ASSERT_EQ(person->getName(), "John");
  ASSERT_EQ(person->getCpf(), "167.317.040-40");
  ASSERT_EQ(person->getRg(), "31.732.999-6");
  ASSERT_EQ(person->getBirthday(), "01/01/2000");
  ASSERT_EQ(std::static_pointer_cast<person::Seller>(person)->getOffice(),
            "Joao Pessoa");
}