#pragma once

#include "database-connector.h"
#include "ui_login-window.h"
#include <QWidget>

namespace ui {
class LoginWindow : public QMainWindow {
public:
  LoginWindow(QWidget *parent = nullptr);

  ~LoginWindow();

  void on_btnLogin_pressed();

private:
  Ui::LoginWindow *ui;
  database::DatabaseConnector dbConn;
};
} // namespace ui
