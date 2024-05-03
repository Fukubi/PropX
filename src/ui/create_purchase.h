#pragma once

#include "purchase.h"
#include "ui_create-purchase.h"
#include "user.h"
#include <QMainWindow>
#include <database-connector.h>

namespace ui {
class CreatePurchase : public QMainWindow {
  Q_OBJECT
public:
  CreatePurchase(std::shared_ptr<user::User> user = nullptr,
                 QWidget *parent = nullptr);

  void updateAvailableProperties();

  void updateAvailableClientUsers();

  void updateComboBoxProperty(QComboBox *comboBox);

  void updateComboBoxClientUsers(QComboBox *comboBox);

  void updateComboBoxPaymentMethods();

public slots:
  void on_combo_box_index_changed();

  void on_btn_create_purchased_pressed();

signals:
  void on_new_purchase_signal();

private:
  std::shared_ptr<user::User> loggedUser;
  std::vector<std::shared_ptr<user::User>> availableClientUsers;
  Ui::CreatePurchase *ui;
  database::DatabaseConnector dbCon;
  std::vector<std::shared_ptr<property::Property>> availableProperties;
  std::vector<QComboBox *> existingComboBoxs;
};
} // namespace ui
