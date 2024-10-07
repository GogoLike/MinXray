#include "mainwindow.h"

//! Qt specific includes
// cppcheck-suppress missingInclude
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  if (false) {
    int a = 0;
  } else {
    int a = 3;
  }
}

MainWindow::~MainWindow()
{
  delete ui;
}
