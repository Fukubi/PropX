#include "home_window.h"
#include "create_property.h"
#include <spdlog/spdlog.h>

namespace ui {
HomeWindow::HomeWindow(std::shared_ptr<user::User> user, QWidget *parent)
    : QMainWindow(parent), ui{new Ui::Home} {
  ui->setupUi(this);
  this->user = user;

  if (user->getAuthorization() != user::Authorization::ADMINISTRATOR) {
    ui->btnCreateUser->hide();
  }

  if (user->getAuthorization() == user::Authorization::CLIENT) {
    ui->btnCreateProperty->hide();
    ui->btnCreatePurchase->hide();
  }

  connect(ui->btnCreateProperty, &QPushButton::pressed, this,
          &HomeWindow::on_btnCreateProperty_pressed);

  initializeTables();
}

HomeWindow::~HomeWindow() { delete ui; }

void HomeWindow::initializeTables() {
  initializePropertiesTable();
  initializePurchasesTable();
}

void HomeWindow::initializePropertiesTable() {
  ui->tblProprerties->clear();
  ui->tblProprerties->setRowCount(0);
  ui->tblProprerties->setColumnCount(10);
  ui->tblProprerties->setHorizontalHeaderLabels(QStringList() << "ID"
                                                              << "Número"
                                                              << "Preço"
                                                              << "Quartos"
                                                              << "Tamanho (m^2)"
                                                              << "Estado"
                                                              << "Rua"
                                                              << "Cidade"
                                                              << "Bairro"
                                                              << "Mobiliado");

  std::vector<std::shared_ptr<property::Property>> properties =
      dbConn.listProperties();

  for (auto property : properties) {
    int currRowCount = ui->tblProprerties->rowCount() + 1;
    int lineNumber = currRowCount - 1;
    ui->tblProprerties->setRowCount(currRowCount);

    QTableWidgetItem *item = new QTableWidgetItem();
    item->setText(QString::fromStdString(std::to_string(property->getId())));
    ui->tblProprerties->setItem(lineNumber, 0, item);

    item = new QTableWidgetItem();
    item->setText(
        QString::fromStdString(std::to_string(property->getNumber())));
    ui->tblProprerties->setItem(lineNumber, 1, item);

    item = new QTableWidgetItem();
    item->setText(QString::fromStdString(std::to_string(property->getPrice())));
    ui->tblProprerties->setItem(lineNumber, 2, item);

    item = new QTableWidgetItem();
    item->setText(
        QString::fromStdString(std::to_string(property->getQtdFloors())));
    ui->tblProprerties->setItem(lineNumber, 3, item);

    item = new QTableWidgetItem();
    item->setText(QString::fromStdString(std::to_string(property->getSize())));
    ui->tblProprerties->setItem(lineNumber, 4, item);

    item = new QTableWidgetItem();
    item->setText(QString::fromStdString(property->getState()));
    ui->tblProprerties->setItem(lineNumber, 5, item);

    item = new QTableWidgetItem();
    item->setText(QString::fromStdString(property->getStreet()));
    ui->tblProprerties->setItem(lineNumber, 6, item);

    item = new QTableWidgetItem();
    item->setText(QString::fromStdString(property->getCity()));
    ui->tblProprerties->setItem(lineNumber, 7, item);

    item = new QTableWidgetItem();
    item->setText(QString::fromStdString(property->getDistrict()));
    ui->tblProprerties->setItem(lineNumber, 8, item);

    item = new QTableWidgetItem();
    if (property->getIsMobiliated()) {
      item->setText("Sim");
    } else {
      item->setText("Não");
    }
    item->setSelected(property->getIsMobiliated());
    ui->tblProprerties->setItem(lineNumber, 9, item);
  }
}

void HomeWindow::initializePurchasesTable() {
  ui->tblPurchases->clear();
  ui->tblPurchases->setRowCount(0);
  ui->tblPurchases->setColumnCount(5);
  ui->tblPurchases->setHorizontalHeaderLabels(QStringList()
                                              << "ID"
                                              << "Cliente"
                                              << "Vendedor"
                                              << "Método de Pagamento"
                                              << "Status de Pagamento");

  std::vector<std::shared_ptr<purchase::Purchase>> purchases =
      dbConn.listPurchases();

  for (auto purchase : purchases) {
    int currRowCount = ui->tblPurchases->rowCount() + 1;
    int lineNumber = currRowCount - 1;
    ui->tblPurchases->setRowCount(currRowCount);

    QTableWidgetItem *item = new QTableWidgetItem();
    item->setText(QString::fromStdString(std::to_string(purchase->getId())));
    ui->tblPurchases->setItem(lineNumber, 0, item);

    item = new QTableWidgetItem();
    item->setText(QString::fromStdString(
        purchase->getUserClient()->getPerson()->getName()));
    ui->tblPurchases->setItem(lineNumber, 1, item);

    item = new QTableWidgetItem();
    item->setText(QString::fromStdString(
        purchase->getUserSeller()->getPerson()->getName()));
    ui->tblPurchases->setItem(lineNumber, 2, item);

    item = new QTableWidgetItem();
    if (purchase->getPaymentMethod() == purchase::PaymentMethod::BANK_SLIP) {
      item->setText("Boleto");
    } else if (purchase->getPaymentMethod() ==
               purchase::PaymentMethod::BERRIES) {
      item->setText("Berries");
    } else if (purchase->getPaymentMethod() ==
               purchase::PaymentMethod::CREDIT_CARD) {
      item->setText("Cartão de Crédito");
    } else if (purchase->getPaymentMethod() ==
               purchase::PaymentMethod::DEBIT_CARD) {
      item->setText("Cartão de Débito");
    } else if (purchase->getPaymentMethod() == purchase::PaymentMethod::MONEY) {
      item->setText("Dinheiro");
    } else {
      item->setText("Pix");
    }
    ui->tblPurchases->setItem(lineNumber, 3, item);

    item = new QTableWidgetItem();
    if (purchase->getPaymentStatus() == purchase::PaymentStatus::ACCEPTED) {
      item->setText("Aceito");
    } else if (purchase->getPaymentStatus() ==
               purchase::PaymentStatus::CANCELED) {
      item->setText("Cancelado");
    } else if (purchase->getPaymentStatus() ==
               purchase::PaymentStatus::PENDING) {
      item->setText("Pendente");
    } else {
      item->setText("Rejeitado");
    }
    ui->tblPurchases->setItem(lineNumber, 4, item);
  }
}

void HomeWindow::on_btnCreateProperty_pressed() {
    CreateProperty *createProperty = new CreateProperty(this);

    createProperty->show();
}

} // namespace ui
