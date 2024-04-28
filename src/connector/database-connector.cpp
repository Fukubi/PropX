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
              ", " + txn.quote(office) + ", " +
              pqxx::to_string(static_cast<int>(type)) + ");");

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

    txn.exec0(
        "INSERT INTO purchase (user_client_id, user_seller_id, "
        "payment_method, payment_status) VALUES (" +
        pqxx::to_string(purchase->getUserClient()->getId()) + ", " +
        pqxx::to_string(purchase->getUserSeller()->getId()) + ", " +
        pqxx::to_string(static_cast<int>(purchase->getPaymentMethod())) + ", " +
        pqxx::to_string(static_cast<int>(purchase->getPaymentStatus())) + ");");

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
        ", " + pqxx::to_string(static_cast<int>(user->getAuthorization())) +
        ", " + pqxx::to_string(user->getPerson()->getId()) + ");");

    txn.commit();
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }
}

std::vector<std::shared_ptr<person::Person>> DatabaseConnector::listPersons() {
  std::vector<std::shared_ptr<person::Person>> persons;

  try {
    pqxx::work txn{conn};

    pqxx::result res{txn.exec("SELECT * FROM persons;")};

    txn.commit();

    for (auto row : res) {
      std::shared_ptr<person::Person> person;

      if (row["type"].as<int>() == PersonType::CLIENT_PJ) {
        person = std::make_shared<person::ClientPJ>(row["id"].as<long>());
        std::static_pointer_cast<person::ClientPJ>(person)->setCnpj(
            row["cnpj"].c_str());
      } else if (row["type"].as<int>() == PersonType::SELLER) {
        person = std::make_shared<person::Seller>(row["id"].as<long>());
        std::static_pointer_cast<person::Seller>(person)->setOffice(
            row["office"].c_str());
      } else {
        person = std::make_shared<person::ClientPF>(row["id"].as<long>());
      }

      person->setName(row["name"].c_str());
      person->setCpf(row["cpf"].c_str());
      person->setRg(row["rg"].c_str());
      person->setBirthday(row["birthday"].c_str());

      persons.push_back(person);
    }
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }

  return persons;
}

std::shared_ptr<person::Person> DatabaseConnector::getPersonById(long id) {
  std::shared_ptr<person::Person> person;

  try {
    pqxx::work txn{conn};

    pqxx::result res{txn.exec(
        "SELECT * FROM persons WHERE id = " + pqxx::to_string(id) + ";")};
    txn.commit();

    for (auto row : res) {
      if (row["type"].as<int>() == PersonType::CLIENT_PJ) {
        person = std::make_shared<person::ClientPJ>(row["id"].as<long>());
        std::static_pointer_cast<person::ClientPJ>(person)->setCnpj(
            row["cnpj"].c_str());
      } else if (row["type"].as<int>() == PersonType::SELLER) {
        person = std::make_shared<person::Seller>(row["id"].as<long>());
        std::static_pointer_cast<person::Seller>(person)->setOffice(
            row["office"].c_str());
      } else {
        person = std::make_shared<person::ClientPF>(row["id"].as<long>());
      }

      person->setName(row["name"].c_str());
      person->setCpf(row["cpf"].c_str());
      person->setRg(row["rg"].c_str());
      person->setBirthday(row["birthday"].c_str());
    }
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }

  return person;
}

std::vector<std::shared_ptr<property::Property>>
DatabaseConnector::listProperties() {
  std::vector<std::shared_ptr<property::Property>> properties;

  try {
    pqxx::work txn{conn};

    pqxx::result res{txn.exec("SELECT * FROM properties;")};

    txn.commit();

    for (auto row : res) {
      std::shared_ptr<property::Property> property =
          std::make_shared<property::Property>(row["id"].as<long>());

      property->setNumber(row["number"].as<int>());
      property->setPrice(row["price"].as<float>());
      property->setQtdFloors(row["qtd_floors"].as<int>());
      property->setSize(row["size"].as<float>());
      property->setState(row["state"].c_str());
      property->setStreet(row["street"].c_str());
      property->setCity(row["city"].c_str());
      property->setDistrict(row["district"].c_str());
      property->setIsMobiliated(row["isMobiliated"].as<bool>());
      property->setCoordinates('x', row["x_coordinates"].as<double>());
      property->setCoordinates('y', row["y_coordinates"].as<double>());

      properties.push_back(property);
    }
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }

  return properties;
}

std::vector<std::shared_ptr<property::Property>>
DatabaseConnector::listPropertiesOfPurchase(long purchase_id) {
  std::vector<std::shared_ptr<property::Property>> properties;

  try {
    pqxx::work txn{conn};

    pqxx::result res{txn.exec(
        "SELECT * FROM properties WHERE id in (select id_property from "
        "purchase_property where id_purchase = " +
        pqxx::to_string(purchase_id) + ");")};

    txn.commit();

    for (auto row : res) {
      std::shared_ptr<property::Property> property =
          std::make_shared<property::Property>(row["id"].as<long>());

      property->setNumber(row["number"].as<int>());
      property->setPrice(row["price"].as<float>());
      property->setQtdFloors(row["qtd_floors"].as<int>());
      property->setSize(row["size"].as<float>());
      property->setState(row["state"].c_str());
      property->setStreet(row["street"].c_str());
      property->setCity(row["city"].c_str());
      property->setDistrict(row["district"].c_str());
      property->setIsMobiliated(row["isMobiliated"].as<bool>());
      property->setCoordinates('x', row["x_coordinates"].as<double>());
      property->setCoordinates('y', row["y_coordinates"].as<double>());

      properties.push_back(property);
    }
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }

  return properties;
}

std::vector<std::shared_ptr<purchase::Purchase>>
DatabaseConnector::listPurchases() {
  std::vector<std::shared_ptr<purchase::Purchase>> purchases;

  try {
    pqxx::work txn{conn};

    pqxx::result resPurchase{txn.exec("SELECT * FROM purchase;")};

    txn.commit();

    for (auto row : resPurchase) {
      std::shared_ptr<purchase::Purchase> purchase =
          std::make_shared<purchase::Purchase>(row["id"].as<long>());

      purchase->setUserClient(getUserById(row["user_client_id"].as<long>()));
      purchase->setUserSeller(getUserById(row["user_seller_id"].as<long>()));
      purchase->setPaymentMethod(static_cast<purchase::PaymentMethod>(
          row["payment_method"].as<int>()));
      purchase->setPaymentStatus(static_cast<purchase::PaymentStatus>(
          row["payment_status"].as<int>()));

      std::vector<std::shared_ptr<property::Property>> properties =
          listPropertiesOfPurchase(purchase->getId());

      for (int i = 0; i < properties.size(); i++) {
        purchase->addProperty(properties[i]);
      }

      purchases.push_back(purchase);
    }
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }

  return purchases;
}

std::shared_ptr<user::User> DatabaseConnector::getUserById(long id) {
  std::shared_ptr<user::User> user;

  try {
    pqxx::work txn{conn};

    pqxx::result resUser{txn.exec(
        "SELECT * FROM users WHERE id = " + pqxx::to_string(id) + ";")};
    txn.commit();

    for (auto row : resUser) {
      user = std::make_shared<user::User>(
          static_cast<user::Authorization>(row["auth"].as<int>()),
          row["id"].as<long>());

      user->setUsername(row["username"].c_str());
      user->setPassword(row["password"].c_str());
      user->setPerson(getPersonById(row["person_id"].as<long>()));
      user->setEncryption(std::make_unique<cryptography::BCrypt>());
    }
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }

  return user;
}

std::shared_ptr<user::User>
DatabaseConnector::getUserByUsername(std::string username) {
  std::shared_ptr<user::User> user;

  try {
    pqxx::work txn{conn};

    pqxx::result resUser{txn.exec(
        "SELECT * FROM users WHERE username = " + txn.quote(username) + ";")};

    txn.commit();

    for (auto row : resUser) {
      user = std::make_shared<user::User>(
          static_cast<user::Authorization>(row["auth"].as<int>()),
          row["id"].as<long>());

      user->setUsername(row["username"].c_str());
      user->setPassword(row["password"].c_str());
      user->setPerson(getPersonById(row["person_id"].as<long>()));
      user->setEncryption(std::make_unique<cryptography::BCrypt>());
    }
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }

  return user;
}

void DatabaseConnector::updatePerson(std::shared_ptr<person::Person> person,
                                     PersonType type) {
  try {
    pqxx::work txn{conn};

    std::string cnpj = "";
    std::string office = "";

    if (type == PersonType::CLIENT_PJ)
      cnpj = std::static_pointer_cast<person::ClientPJ>(person)->getCnpj();

    if (type == PersonType::SELLER)
      office = std::static_pointer_cast<person::Seller>(person)->getOffice();

    txn.exec0("UPDATE persons (name, cpf, rg, birthday, cnpj, office, "
              "type) SET name = " +
              txn.quote(person->getName()) +
              ", cpf = " + txn.quote(person->getCpf()) +
              ", rg = " + txn.quote(person->getRg()) +
              ", birthday = " + txn.quote(person->getBirthday()) + ", cnpj " +
              txn.quote(cnpj) + ", office = " + txn.quote(office) +
              ", type = " + pqxx::to_string(static_cast<int>(type)) +
              " WHERE id = " + pqxx::to_string(person->getId()) + ";");

    txn.commit();
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }
}

void DatabaseConnector::updateProperty(
    std::shared_ptr<property::Property> property) {
  try {
    pqxx::work txn{conn};

    txn.exec0(
        "UPDATE properties (number, price, qtd_floors, size, state, "
        "street, "
        "city, district, isMobiliated, x_coordinates, y_coordinates) SET "
        "number = " +
        pqxx::to_string(property->getNumber()) +
        ", price = " + pqxx::to_string(property->getPrice()) +
        ", qtd_floors = " + pqxx::to_string(property->getQtdFloors()) +
        ", size = " + pqxx::to_string(property->getSize()) +
        ", state = " + txn.quote(property->getState()) +
        ", street = " + txn.quote(property->getStreet()) +
        ", city = " + txn.quote(property->getCity()) +
        ", district = " + txn.quote(property->getDistrict()) +
        ", isMobiliated = " + pqxx::to_string(property->getIsMobiliated()) +
        ", x_coordinates = " + pqxx::to_string(property->getCoordinates('x')) +
        ", y_coordinates = " + pqxx::to_string(property->getCoordinates('y')) +
        ") WHERE id = " + pqxx::to_string(property->getId()) + ";");

    txn.commit();
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }
}

void DatabaseConnector::updatePurchase(
    std::shared_ptr<purchase::Purchase> purchase) {
  try {
    pqxx::work txn{conn};

    txn.exec0("INSERT purchase (user_client_id, user_seller_id, "
              "payment_method, payment_status) SET user_client_id = " +
              pqxx::to_string(purchase->getUserClient()->getId()) +
              ", user_seller_id = " +
              pqxx::to_string(purchase->getUserSeller()->getId()) +
              ", payment_method = " +
              pqxx::to_string(static_cast<int>(purchase->getPaymentMethod())) +
              ", payment_status = " +
              pqxx::to_string(static_cast<int>(purchase->getPaymentStatus())) +
              " WHERE id = " + pqxx::to_string(purchase->getId()) + ");");

    txn.commit();
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }
}

void DatabaseConnector::updateUser(std::shared_ptr<user::User> user) {
  try {
    pqxx::work txn{conn};

    txn.exec0("INSERT INTO users (username, password, auth, person_id) SET "
              "username = " +
              txn.quote(user->getUsername()) +
              ", password = " + txn.quote(user->getPassword()) + ", auth = " +
              pqxx::to_string(static_cast<int>(user->getAuthorization())) +
              ", person_id = " + pqxx::to_string(user->getPerson()->getId()) +
              ") WHERE id = " + pqxx::to_string(user->getId()) + ";");

    txn.commit();
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }
}

void DatabaseConnector::deletePerson(long id) {
  try {
    pqxx::work txn{conn};

    txn.exec0("DELETE FROM persons WHERE id = " + pqxx::to_string(id) + ");");

    txn.commit();
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }
}

void DatabaseConnector::deleteProperty(long id) {
  try {
    pqxx::work txn{conn};

    txn.exec0("DELETE FROM properties WHERE id = " + pqxx::to_string(id) +
              ");");

    txn.commit();
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }
}

void DatabaseConnector::deletePurchase(long id) {
  try {
    pqxx::work txn{conn};

    txn.exec0("DELETE FROM purchase WHERE id = " + pqxx::to_string(id) + ");");

    txn.commit();
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }
}

void DatabaseConnector::deleteUser(long id) {
  try {
    pqxx::work txn{conn};

    txn.exec0("DELETE FROM users WHERE id = " + pqxx::to_string(id) + ");");

    txn.commit();
  } catch (const std::exception &e) {
    spdlog::error(e.what());
  }
}

} // namespace database
