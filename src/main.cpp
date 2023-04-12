#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  setenv("LC_NUMERIC", "en_US.UTF-8", 1);
  QApplication app(argc, argv);
  MainWindow w;
  w.show();
  return app.exec();
}
