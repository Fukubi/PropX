#pragma once

#include "ui_create-property.h"
#include <QMainWindow>

namespace ui {
class CreateProperty : public QMainWindow {
  Q_OBJECT
public:
  CreateProperty(QWidget *parent = nullptr);

  void on_btnRegister_pressed();

signals:
  void on_new_property_signal();

private:
  Ui::CreateProperty *ui;
};
} // namespace ui
