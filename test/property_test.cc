#include "property.h"
#include <gtest/gtest.h>

TEST(PropertyTest, Initialization) {
  std::shared_ptr<property::Property> property =
      std::make_shared<property::Property>();

  ASSERT_EQ(property->getQtdFloors(), 0);
  ASSERT_EQ(property->getNumber(), 0);
  ASSERT_EQ(property->getSize(), 0);
  ASSERT_EQ(property->getPrice(), 0);
  ASSERT_FALSE(property->getIsMobiliated());
  ASSERT_STREQ(property->getStreet().c_str(), "");
  ASSERT_STREQ(property->getDistrict().c_str(), "");
  ASSERT_STREQ(property->getState().c_str(), "");
  ASSERT_STREQ(property->getCity().c_str(), "");
  ASSERT_EQ(property->getCoordinates('x'), 0);
  ASSERT_EQ(property->getCoordinates('y'), 0);
}

TEST(PropertyTest, ValuesCantBeNegative) {
  std::shared_ptr<property::Property> property =
      std::make_shared<property::Property>();

  property->setQtdFloors(-1);
  property->setNumber(-1);
  property->setSize(-1);
  property->setPrice(-1);

  ASSERT_EQ(property->getQtdFloors(), 0);
  ASSERT_EQ(property->getNumber(), 0);
  ASSERT_EQ(property->getSize(), 0);
  ASSERT_EQ(property->getPrice(), 0);
}

TEST(PropertyTest, SetsShouldChangeValues) {
  std::shared_ptr<property::Property> property =
      std::make_shared<property::Property>();

  property->setQtdFloors(1);
  property->setNumber(203);
  property->setSize(50);
  property->setPrice(40000);
  property->setIsMobiliated(true);
  property->setStreet("Rua nao existente");
  property->setDistrict("Destrito de teste");
  property->setState("Novo estado");
  property->setCity("Pedra branca");
  property->setCoordinates('x', -7.427104447161748);
  property->setCoordinates('y', -38.069099913406326);


  ASSERT_EQ(property->getQtdFloors(), 1);
  ASSERT_EQ(property->getNumber(), 203);
  ASSERT_EQ(property->getSize(), 50);
  ASSERT_EQ(property->getPrice(), 40000);
  ASSERT_TRUE(property->getIsMobiliated());
  ASSERT_STREQ(property->getStreet().c_str(), "Rua nao existente");
  ASSERT_STREQ(property->getDistrict().c_str(), "Destrito de teste");
  ASSERT_STREQ(property->getState().c_str(), "Novo estado");
  ASSERT_STREQ(property->getCity().c_str(), "Pedra branca");
  ASSERT_EQ(property->getCoordinates('x'), -7.427104447161748);
  ASSERT_EQ(property->getCoordinates('y'), -38.069099913406326);
}