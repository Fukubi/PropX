#pragma once

#include "database-connector.h"
#include "ui_home-window.h"
#include <QMainWindow>
#include <user.h>

namespace ui {
class HomeWindow : public QMainWindow {
public:
  HomeWindow(std::shared_ptr<user::User> user, QWidget *parent = nullptr);
  ~HomeWindow();

  void initializeTables();

  void initializePropertiesTable();

  void initializePurchasesTable();

private:
  Ui::Home *ui;
  std::shared_ptr<user::User> user;
  database::DatabaseConnector dbConn;
};
} // namespace ui
