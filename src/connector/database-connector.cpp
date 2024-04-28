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

void DatabaseConnector::savePerson(std::shared_ptr<person::Person> person,
                                   PersonType type) {
  try {
    pqxx::work txn{conn};

    std::string cnpj = "";
    std::string office = "";

    if (type == PersonType::CLIENT_PJ)
      cnpj = std::static_pointer_cast<person::ClientPJ>(person)->getCnpj();

    if (type == PersonType::SELLER)
      office = std::static_pointer_cast<person::Seller>(person)->getOffice();

    txn.exec0("INSERT INTO persons (name, cpf, rg, birthday, cnpj, office, "
              "type) VALUES (" +
              txn.quote(person->getName()) + ", " +
              txn.quote(person->getCpf()) + ", " + txn.quote(person->getRg()) +
              ", " + txn.quote(person->getBirthday()) + ", " + txn.quote(cnpj) +
              ", " + txn.quote(office) + ", " + pqxx::to_string(type) + ");");

    txn.commit();
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }
}

void DatabaseConnector::saveProperty(
    std::shared_ptr<property::Property> property) {
  try {
    pqxx::work txn{conn};

    txn.exec0(
        "INSERT INTO properties (number, price, qtd_floors, size, state, "
        "street, "
        "city, district, isMobiliated, x_coordinates, y_coordinates) VALUES (" +
        pqxx::to_string(property->getNumber()) + ", " +
        pqxx::to_string(property->getPrice()) + ", " +
        pqxx::to_string(property->getQtdFloors()) + ", " +
        pqxx::to_string(property->getSize()) + ", " +
        txn.quote(property->getState()) + ", " +
        txn.quote(property->getStreet()) + ", " +
        txn.quote(property->getCity()) + ", " +
        txn.quote(property->getDistrict()) + ", " +
        pqxx::to_string(property->getIsMobiliated()) + ", " +
        pqxx::to_string(property->getCoordinates('x')) + ", " +
        pqxx::to_string(property->getCoordinates('y')) + ");");

    txn.commit();
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }
}

void DatabaseConnector::savePurchase(
    std::shared_ptr<purchase::Purchase> purchase) {
  try {
    pqxx::work txn{conn};

    txn.exec0("INSERT INTO purchase (user_client_id, user_seller_id, "
              "payment_method, payment_status) VALUES (" +
              pqxx::to_string(purchase->getUserClient()->getId()) + ", " +
              pqxx::to_string(purchase->getUserSeller()->getId()) + ", " +
              pqxx::to_string(purchase->getPaymentMethod()) + ", " +
              pqxx::to_string(purchase->getPaymentStatus()) + ");");

    for (size_t i = 0; i < purchase->getQtdProperties(); i++) {
      std::shared_ptr<property::Property> property = purchase->getProperty(i);

      txn.exec0("INSERT INTO purchase_property VALUES (" +
                pqxx::to_string(purchase->getId()) + ", " +
                pqxx::to_string(property->getId()) + ");");
    }

    txn.commit();
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }
}

void DatabaseConnector::saveUser(std::shared_ptr<user::User> user) {
  try {
    pqxx::work txn{conn};

    txn.exec0(
        "INSERT INTO users (username, password, auth, person_id) VALUES (" +
        txn.quote(user->getUsername()) + ", " + txn.quote(user->getPassword()) +
        ", " + pqxx::to_string(user->getAuthorization()) + ", " +
        pqxx::to_string(user->getPerson()->getId()) + ");");

    txn.commit();
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }
}

} // namespace database
