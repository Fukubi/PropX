#include "create_purchase.h"

namespace ui {
CreatePurchase::CreatePurchase(std::shared_ptr<user::User> user,
                               QWidget *parent)
    : loggedUser(user), QMainWindow(parent), ui{new Ui::CreatePurchase} {
  ui->setupUi(this);

  this->updateAvailableProperties();

  this->existingComboBoxs.push_back(ui->ComboProperty);

  this->updateComboBoxClientUsers(ui->comboUserClient);

  this->updateComboBoxProperty(ui->ComboProperty);

  this->updateComboBoxPaymentMethods();

  connect(ui->ComboProperty, &QComboBox::currentIndexChanged, this,
          &CreatePurchase::on_combo_box_index_changed);
}

void CreatePurchase::updateAvailableProperties() {
  this->availableProperties = this->dbCon.listPropertiesNotPurchased();
}

void CreatePurchase::updateAvailableClientUsers() {
  this->availableClientUsers = this->dbCon.listClientUsers();
}

void CreatePurchase::updateComboBoxProperty(QComboBox *comboBox) {
  for (const auto &property : this->availableProperties) {
    QString displayText = QString::fromStdString(
        property->getCity() + ", " + property->getDistrict() + ", " +
        property->getStreet() + " " + std::to_string(property->getNumber()));

    comboBox->addItem(displayText);

    QVariant propertyData = QVariant::fromValue(property);
    comboBox->setItemData(comboBox->count() - 1, propertyData, Qt::UserRole);
  }
}

void CreatePurchase::updateComboBoxClientUsers(QComboBox *comboBox) {
  for (const auto &user : this->availableClientUsers) {
    QString displayText = QString::fromStdString(user->getUsername());

    comboBox->addItem(displayText);

    QVariant userData = QVariant::fromValue(user);
    comboBox->setItemData(comboBox->count() - 1, userData, Qt::UserRole);
  }
}

void CreatePurchase::updateComboBoxPaymentMethods() {
  QString displayText = "Cartão de Débito";

  ui->comboPaymentMethod->addItem(displayText);

  QVariant paymentMethodData =
      QVariant::fromValue(purchase::PaymentMethod::DEBIT_CARD);
  ui->comboPaymentMethod->setItemData(ui->comboPaymentMethod->count() - 1, paymentMethodData, Qt::UserRole);

  displayText = "Cartão de Crédito";

  ui->comboPaymentMethod->addItem(displayText);

  paymentMethodData =
      QVariant::fromValue(purchase::PaymentMethod::CREDIT_CARD);
  ui->comboPaymentMethod->setItemData(ui->comboPaymentMethod->count() - 1, paymentMethodData, Qt::UserRole);

  displayText = "Dinheiro";

  ui->comboPaymentMethod->addItem(displayText);

  paymentMethodData =
      QVariant::fromValue(purchase::PaymentMethod::MONEY);
  ui->comboPaymentMethod->setItemData(ui->comboPaymentMethod->count() - 1, paymentMethodData, Qt::UserRole);

  displayText = "Pix";

  ui->comboPaymentMethod->addItem(displayText);

  paymentMethodData =
      QVariant::fromValue(purchase::PaymentMethod::PIX);
  ui->comboPaymentMethod->setItemData(ui->comboPaymentMethod->count() - 1, paymentMethodData, Qt::UserRole);

  displayText = "Boleto Bancário";

  ui->comboPaymentMethod->addItem(displayText);

  paymentMethodData =
      QVariant::fromValue(purchase::PaymentMethod::BANK_SLIP);
  ui->comboPaymentMethod->setItemData(ui->comboPaymentMethod->count() - 1, paymentMethodData, Qt::UserRole);

  displayText = "Berries";

  ui->comboPaymentMethod->addItem(displayText);

  paymentMethodData =
      QVariant::fromValue(purchase::PaymentMethod::BERRIES);
  ui->comboPaymentMethod->setItemData(ui->comboPaymentMethod->count() - 1, paymentMethodData, Qt::UserRole);
}

void CreatePurchase::on_btn_create_purchased_pressed() {
  std::shared_ptr<purchase::Purchase> purchase =
      std::make_shared<purchase::Purchase>();

  std::shared_ptr<user::User> user =
      ui->comboUserClient->currentData().value<std::shared_ptr<user::User>>();

  purchase->setUserSeller(loggedUser);
  purchase->setUserClient(user);
  purchase->setPaymentMethod(
      ui->comboPaymentMethod->currentData().value<purchase::PaymentMethod>());
  purchase->setPaymentStatus(purchase::PaymentStatus::PENDING);

  for (auto &comboBoxProperty : this->existingComboBoxs) {
    std::shared_ptr<property::Property> property =
        comboBoxProperty->currentData()
            .value<std::shared_ptr<property::Property>>();
    purchase->addProperty(property);
  }

  dbCon.savePurchase(purchase);
}

void CreatePurchase::on_combo_box_index_changed() {
  QComboBox *senderComboBox = qobject_cast<QComboBox *>(sender());
  if (!senderComboBox)
    return;

  if (senderComboBox != this->existingComboBoxs.back())
    return;

  QComboBox *newComboBox = new QComboBox(this);
  this->updateComboBoxProperty(newComboBox);

  this->existingComboBoxs.push_back(newComboBox);

  connect(newComboBox, &QComboBox::currentIndexChanged, this,
          &CreatePurchase::on_combo_box_index_changed);

  ui->comboPropertyLayout->addWidget(newComboBox);
}
} // namespace ui
