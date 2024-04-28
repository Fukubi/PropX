#include <iostream>
#include <login_window.h>

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  ui::LoginWindow loginWindow;

  loginWindow.show();

  return a.exec();
}