#include "mainwindow.h"

//! Qt specific includes
// cppcheck-suppress missingIncludeSystem
#include <QApplication>

int
main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  MainWindow window;
  window.show();

  return app.exec();
}
