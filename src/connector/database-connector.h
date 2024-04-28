#pragma once

#include "person.h"
#include "property.h"
#include "purchase.h"
#include <pqxx/pqxx>
#include <vector>

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

  std::vector<std::shared_ptr<person::Person>> listPersons();

  std::shared_ptr<person::Person> getPersonById(long id);

  std::vector<std::shared_ptr<property::Property>> listProperties();

  std::vector<std::shared_ptr<property::Property>>
  listPropertiesOfPurchase(long purchase_id);

  std::vector<std::shared_ptr<purchase::Purchase>> listPurchases();

  std::shared_ptr<user::User> getUserById(long id);

  std::shared_ptr<user::User> getUserByUsername(std::string username);

  void updatePerson(std::shared_ptr<person::Person> person, PersonType type);

  void updateProperty(std::shared_ptr<property::Property> property);

  void updatePurchase(std::shared_ptr<purchase::Purchase> purchase);

  void updateUser(std::shared_ptr<user::User> user);

  void deletePerson(long id);

  void deleteProperty(long id);

  void deletePurchase(long id);

  void deleteUser(long id);

private:
  /// @brief The connection of the database
  pqxx::connection conn;
};
} // namespace database
