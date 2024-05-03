#include "create_user.h"

namespace ui {
CreateUser::CreateUser(std::shared_ptr<user::User> user, QWidget *parent)
    : loggedUser(user), QMainWindow(parent), ui{new Ui::CreateUser} {
  ui->setupUi(this);

  this->updateAvailablePersons();

  this->updateAuthCombobox();

  this->updatePersonsCombobox();

  connect(ui->btnSave, &QPushButton::pressed, this,
          &CreateUser::on_btnSave_pressed);
}

void CreateUser::updateAvailablePersons() {
  this->availablePersons = dbConn.listNotRegisteredPersons();
}

void CreateUser::updateAuthCombobox() {
  QString displayText;
  QVariant authorizationData;

  if (loggedUser->getAuthorization() == user::Authorization::ADMINISTRATOR) {
    displayText = "Administrador";

    ui->comboAuthorization->addItem(displayText);

    authorizationData = QVariant::fromValue(user::Authorization::ADMINISTRATOR);
    ui->comboAuthorization->setItemData(ui->comboAuthorization->count() - 1,
                                        authorizationData, Qt::UserRole);

    displayText = "Vendedor";

    ui->comboAuthorization->addItem(displayText);

    authorizationData = QVariant::fromValue(user::Authorization::SELLER);
    ui->comboAuthorization->setItemData(ui->comboAuthorization->count() - 1,
                                        authorizationData, Qt::UserRole);
  }

  displayText = "Cliente";

  ui->comboAuthorization->addItem(displayText);

  authorizationData = QVariant::fromValue(user::Authorization::CLIENT);
  ui->comboAuthorization->setItemData(ui->comboAuthorization->count() - 1,
                                      authorizationData, Qt::UserRole);
}

void CreateUser::updatePersonsCombobox() {
  for (const auto &person : this->availablePersons) {
    QString displayText = QString::fromStdString(person->getName());

    ui->comboPerson->addItem(displayText);

    QVariant userData = QVariant::fromValue(person);
    ui->comboPerson->setItemData(ui->comboPerson->count() - 1, userData,
                                 Qt::UserRole);
  }
}

void CreateUser::on_btnSave_pressed() {
  std::string username = ui->editUsername->text().toStdString();
  std::string password = ui->editPassword->text().toStdString();
  user::Authorization authorization =
      ui->comboAuthorization->currentData().value<user::Authorization>();
  std::shared_ptr<person::Person> person =
      ui->comboPerson->currentData().value<std::shared_ptr<person::Person>>();

  std::shared_ptr<user::User> newUser =
      std::make_shared<user::User>(authorization);

  dbConn.saveUser(newUser);
}
} // namespace ui
