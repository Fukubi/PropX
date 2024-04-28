#pragma once

#include "person.h"
#include "property.h"
#include "purchase.h"
#include <pqxx/pqxx>

/// @brief database related namespace
namespace database {
enum PersonType { CLIENT_PF, CLIENT_PJ, SELLER };

/// @brief Classes that execute the connection and run instructions
class DatabaseConnector {
public:
  /// @brief Default constructor, generate the default tables in the database if
  /// they don't exist
  DatabaseConnector();

  void savePerson(std::shared_ptr<person::Person> person, PersonType type);

  void saveProperty(std::shared_ptr<property::Property> property);

  void savePurchase(std::shared_ptr<purchase::Purchase> purchase);

  void saveUser(std::shared_ptr<user::User> user);

private:
  /// @brief The connection of the database
  pqxx::connection conn;
};
} // namespace database
