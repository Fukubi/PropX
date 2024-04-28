#include "purchase.h"

namespace purchase {
Purchase::Purchase()
    : properties(), userClient(nullptr), userSeller(nullptr),
      paymentMethod(PaymentMethod::CREDIT_CARD),
      paymentStatus(PaymentStatus::PENDING), id(0) {}

Purchase::Purchase(long id)
    : properties(), userClient(nullptr), userSeller(nullptr),
      paymentMethod(PaymentMethod::CREDIT_CARD),
      paymentStatus(PaymentStatus::PENDING), id(id) {}

std::shared_ptr<property::Property> Purchase::getProperty(size_t index) {
  if (index >= getQtdProperties())
    return nullptr;

  return this->properties[index];
}

void Purchase::addProperty(std::shared_ptr<property::Property> property) {
  this->properties.push_back(property);
}

size_t Purchase::getQtdProperties() { return this->properties.size(); }

std::shared_ptr<user::User> Purchase::getUserClient() {
  return this->userClient;
}

std::shared_ptr<user::User> Purchase::getUserSeller() {
  return this->userSeller;
}

PaymentMethod Purchase::getPaymentMethod() { return this->paymentMethod; }

PaymentStatus Purchase::getPaymentStatus() { return this->paymentStatus; }

long Purchase::getId() { return this->id; }

void Purchase::setUserClient(std::shared_ptr<user::User> userClient) {
  this->userClient = userClient;
}

void Purchase::setUserSeller(std::shared_ptr<user::User> userSeller) {
  this->userSeller = userSeller;
}

void Purchase::setPaymentMethod(PaymentMethod paymentMethod) {
  this->paymentMethod = paymentMethod;
}
void Purchase::setPaymentStatus(PaymentStatus paymentStatus) {
  this->paymentStatus = paymentStatus;
}
} // namespace purchase
