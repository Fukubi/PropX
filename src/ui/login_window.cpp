#include "login_window.h"

#include "home_window.h"
#include "user.h"
#include <QMainWindow>
#include <iostream>
#include <spdlog/spdlog.h>
#include <string>

namespace ui {
LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent), ui{new Ui::LoginWindow} {
  ui->setupUi(this);

  connect(ui->btnLogin, &QPushButton::pressed, this,
          &LoginWindow::on_btnLogin_pressed);
}

LoginWindow::~LoginWindow() { delete ui; }

void LoginWindow::on_btnLogin_pressed() {
  std::string username = ui->txtUsername->text().toStdString();
  std::string password = ui->txtPassword->text().toStdString();

  std::shared_ptr<user::User> user = dbConn.getUserByUsername(username);

  if (user == nullptr) {
    ui->lblMessage->setText("Incorrect username or password");
    return;
  }

  if (!user->login(password)) {
    ui->lblMessage->setText("Incorrect username or password");
    return;
  }

  ui::HomeWindow *homeWindow = new HomeWindow(user);
  homeWindow->show();

  this->hide();
}
} // namespace ui
