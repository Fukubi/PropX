#pragma once

#include "person.h"
#include "property.h"
#include "user.h"
#include <vector>

/// @brief Namespace for Purchases
namespace purchase {
/// @brief The types of payment method supported
enum PaymentMethod { DEBIT_CARD, CREDIT_CARD, MONEY, PIX, BANK_SLIP, BERRIES };

/// @brief The types of payment status supported
enum PaymentStatus { PENDING, ACCEPTED, REJECTED, CANCELED };

/// @brief The class the stores the Purchase information
class Purchase {
public:
  /// @brief The default constructor with everything empty, the PaymentMethod
  /// set as CREDIT_CARD and the PaymentStatus set as PENDING
  Purchase();

  /// @brief Get the property related to the purchase in specific index
  /// @return The property related to the purchase in the specific index
  std::shared_ptr<property::Property> getProperty(size_t index);

  /// @brief Add a property to this purchase
  /// @param property The new property to be added
  void addProperty(std::shared_ptr<property::Property> property);

  /// @brief Get the quantity of properties in this purchase
  /// @return The quantity of properties in this purchase
  size_t getQtdProperties();

  /// @brief Get the User that bought the properties
  /// @return The User that bought the properties
  std::shared_ptr<user::User> getUserClient();

  /// @brief Get the User that sold the properties
  /// @return The User that sold the properties
  std::shared_ptr<user::User> getUserSeller();

  /// @brief Get the method of payment
  /// @return The method of payment
  PaymentMethod getPaymentMethod();

  /// @brief Get the status of the payment
  /// @return The status of the payment
  PaymentStatus getPaymentStatus();

  /// @brief Set the user of the client that bought the properties
  /// @param userClient The user of the client
  void setUserClient(std::shared_ptr<user::User> userClient);
  /// @brief Set the user of the seller that sold the properties
  /// @param userSeller The user of the seller
  void setUserSeller(std::shared_ptr<user::User> userSeller);
  /// @brief Set the payment method of the purchase
  /// @param paymentMethod The payment method of the purchase
  void setPaymentMethod(PaymentMethod paymentMethod);
  /// @brief Set the payment status of the purchase
  /// @param paymentStatus The payment status of the purchase
  void setPaymentStatus(PaymentStatus paymentStatus);

private:
  /// @brief The properties in this purchase
  std::vector<std::shared_ptr<property::Property>> properties;
  /// @brief The user of the client
  std::shared_ptr<user::User> userClient;
  /// @brief The user of seller
  std::shared_ptr<user::User> userSeller;
  /// @brief The method of payment
  PaymentMethod paymentMethod;
  /// @brief The current status of the payment
  PaymentStatus paymentStatus;
};
} // namespace purchase
