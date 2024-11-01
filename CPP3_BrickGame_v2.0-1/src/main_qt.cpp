/**
 * @file main_qt.cpp
 * @brief  main file for Qt
 */
#include <QApplication>

#include "./gui/desktop/mainwindow.h"

using namespace s21;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
