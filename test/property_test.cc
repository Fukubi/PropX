#include "property.h"
#include <gtest/gtest.h>

TEST(PropertyTest, Initialization) {
  std::shared_ptr<property::Property> property =
      std::make_shared<property::Property>();

  property::Coordinates coordinates = property->getCoordinates();

  ASSERT_EQ(coordinates['x'], 0);
  ASSERT_EQ(coordinates['y'], 0);
  ASSERT_EQ(property->getSize(), 0);
  ASSERT_EQ(property->getQtdRoom(), 0);
  ASSERT_EQ(property->getQtdBathroom(), 0);
  ASSERT_EQ(property->getPrice(), 0);
  ASSERT_FALSE(property->isMobiliated());
  ASSERT_FALSE(property->hasKitchen());
  ASSERT_FALSE(property->hasLivingRoom());
}

TEST(PropertyTest, SetCoordinates) {
  std::shared_ptr<property::Property> property =
      std::make_shared<property::Property>();

  property->setCoordinates(10, 20);

  property::Coordinates coordinates = property->getCoordinates();

  ASSERT_EQ(coordinates['x'], 10);
  ASSERT_EQ(coordinates['y'], 20);
}