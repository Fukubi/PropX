#include "property.h"
#include "purchase.h"
#include "user.h"
#include <gtest/gtest.h>

TEST(PurchaseTest, Initialization) {
  std::unique_ptr<purchase::Purchase> purchase =
      std::make_unique<purchase::Purchase>();

  ASSERT_EQ(purchase->getQtdProperties(), 0);
  ASSERT_EQ(purchase->getUserClient(), nullptr);
  ASSERT_EQ(purchase->getUserSeller(), nullptr);
  ASSERT_EQ(purchase->getPaymentMethod(), purchase::PaymentMethod::CREDIT_CARD);
  ASSERT_EQ(purchase->getPaymentStatus(), purchase::PaymentStatus::PENDING);
}

TEST(PurchaseTest, SetShouldChangeValues) {
  std::unique_ptr<purchase::Purchase> purchase =
      std::make_unique<purchase::Purchase>();

  std::shared_ptr<user::User> userClient = std::make_shared<user::User>();
  userClient->setUsername("client");
  userClient->setPassword("pass");
  purchase->setUserClient(userClient);

  std::shared_ptr<user::User> userSeller =
      std::make_shared<user::User>(user::Authorization::SELLER);
  userSeller->setUsername("seller");
  userSeller->setPassword("pass");
  purchase->setUserSeller(userSeller);

  std::shared_ptr<property::Property> property =
      std::make_shared<property::Property>();
  property->setNumber(203);
  purchase->addProperty(property);

  purchase->setPaymentMethod(purchase::PaymentMethod::DEBIT_CARD);
  purchase->setPaymentStatus(purchase::PaymentStatus::ACCEPTED);

  ASSERT_EQ(purchase->getQtdProperties(), 1);
  ASSERT_EQ(purchase->getUserClient()->getUsername(), "client");
  ASSERT_EQ(purchase->getUserSeller()->getUsername(), "seller");
  ASSERT_EQ(purchase->getPaymentMethod(), purchase::PaymentMethod::DEBIT_CARD);
  ASSERT_EQ(purchase->getPaymentStatus(), purchase::PaymentStatus::ACCEPTED);
}