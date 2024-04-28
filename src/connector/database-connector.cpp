#include "database-connector.h"
#include <spdlog/spdlog.h>

namespace database {
DatabaseConnector::DatabaseConnector()
    : conn{"user=postgres host=localhost password=admin dbname=propx "
           "port=5432"} {
  pqxx::work txn{conn};

  try {
    txn.exec0("CREATE TABLE IF NOT EXISTS persons ("
              "id SERIAL PRIMARY KEY,"
              "name VARCHAR(255) NOT NULL, "
              "cpf VARCHAR(255) NOT NULL, "
              "rg VARCHAR(255) NOT NULL,"
              "birthday VARCHAR(255) NOT NULL,"
              "cnpj VARCHAR(255),"
              "office VARCHAR(255),"
              "type INTEGER NOT NULL"
              ");");

    txn.exec0("CREATE TABLE IF NOT EXISTS properties ("
              "id SERIAL PRIMARY KEY,"
              "number INTEGER NOT NULL,"
              "price FLOAT NOT NULL,"
              "qtd_floors INTEGER NOT NULL,"
              "size FLOAT NOT NULL,"
              "state VARCHAR(255) NOT NULL,"
              "street VARCHAR(255) NOT NULL,"
              "city VARCHAR(255) NOT NULL,"
              "district VARCHAR(255) NOT NULL,"
              "isMobiliated BOOLEAN NOT NULL,"
              "x_coordinates DOUBLE PRECISION NOT NULL,"
              "y_coordinates DOUBLE PRECISION NOT NULL"
              ");");

    txn.exec0("CREATE TABLE IF NOT EXISTS users ("
              "id SERIAL PRIMARY KEY,"
              "username VARCHAR(255) UNIQUE NOT NULL,"
              "password VARCHAR(255) NOT NULL,"
              "auth INTEGER NOT NULL,"
              "person_id INTEGER REFERENCES persons(id)"
              ");");

    txn.exec0("CREATE TABLE IF NOT EXISTS purchase ("
              "id SERIAL PRIMARY KEY,"
              "user_client_id INTEGER REFERENCES users(id),"
              "user_seller_id INTEGER REFERENCES users(id),"
              "payment_method INTEGER NOT NULL,"
              "payment_status INTEGER NOT NULL"
              ");");

    txn.exec0("CREATE TABLE IF NOT EXISTS purchase_property ("
              "id_purchase INTEGER REFERENCES purchase(id),"
              "id_property INTEGER REFERENCES properties(id)"
              ");");

    txn.commit();
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }
}

} // namespace database
