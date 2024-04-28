#pragma once

#include <pqxx/pqxx>

/// @brief database related namespace
namespace database {
/// @brief Classes that execute the connection and run instructions
class DatabaseConnector {
public:
  /// @brief Default constructor, generate the default tables in the database if
  /// they don't exist
  DatabaseConnector();

private:
  /// @brief The connection of the database
  pqxx::connection conn;
};
} // namespace database
