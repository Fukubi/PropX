#pragma once

#include "ui_create-property.h"
#include <QMainWindow>

namespace ui {
class CreateProperty : public QMainWindow {
public:
  CreateProperty(QWidget *parent = nullptr);

  void on_btnRegister_pressed();

private:
  Ui::CreateProperty *ui;
};
} // namespace ui
