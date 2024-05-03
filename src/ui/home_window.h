#pragma once

#include "database-connector.h"
#include "ui_home-window.h"
#include <QMainWindow>
#include <user.h>

namespace ui {
class HomeWindow : public QMainWindow {
  Q_OBJECT
public:
  HomeWindow(std::shared_ptr<user::User> user, QWidget *parent = nullptr);
  ~HomeWindow();

  void initializeTables();

  void initializePropertiesTable();

  void initializePurchasesTable();

  void on_btnCreatePurchase_pressed();

  void on_btnCreateProperty_pressed();

  void on_btnCreateUser_pressed();

public slots:
  void on_new_property_slot();

private:
  Ui::Home *ui;
  std::shared_ptr<user::User> user;
  database::DatabaseConnector dbConn;
};
} // namespace ui
