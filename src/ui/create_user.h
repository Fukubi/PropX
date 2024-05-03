#pragma once

#include "person.h"
#include "ui_create-user.h"
#include "user.h"
#include <QMainWindow>
#include <database-connector.h>
#include <vector>

namespace ui {
class CreateUser : public QMainWindow {
public:
  CreateUser(std::shared_ptr<user::User> user, QWidget *parent = nullptr);

  void updateAvailablePersons();

  void updateAuthCombobox();

  void updatePersonsCombobox();

public slots:
    void on_btnSave_pressed();

private:
  Ui::CreateUser *ui;
  std::shared_ptr<user::User> loggedUser;
  std::vector<std::shared_ptr<person::Person>> availablePersons;
  database::DatabaseConnector dbConn;
};
} // namespace ui
