#include "create_property.h"

#include "database-connector.h"
#include "property.h"

namespace ui {
CreateProperty::CreateProperty(QWidget *parent)
    : QMainWindow(parent), ui{new Ui::CreateProperty} {
  ui->setupUi(this);

  connect(ui->btnRegister, &QPushButton::pressed, this,
          &CreateProperty::on_btnRegister_pressed);
}

void CreateProperty::on_btnRegister_pressed() {
  database::DatabaseConnector dbConn;

  std::shared_ptr<property::Property> property =
      std::make_shared<property::Property>();

  property->setNumber(ui->txtNumber->text().toInt());
  property->setPrice(ui->dblPrice->value());
  property->setQtdFloors(ui->spinRooms->value());
  property->setSize(ui->dblSize->value());
  property->setState(ui->txtState->text().toStdString());
  property->setStreet(ui->txtStreet->text().toStdString());
  property->setCity(ui->txtCity->text().toStdString());
  property->setDistrict(ui->txtDistrict->text().toStdString());
  property->setIsMobiliated(ui->checkIsMobiliated->isChecked());
  property->setCoordinates('x', ui->dblPosX->value());
  property->setCoordinates('y', ui->dblPosY->value());

  dbConn.saveProperty(property);

  emit on_new_property_signal();

  this->hide();
}
} // namespace ui
