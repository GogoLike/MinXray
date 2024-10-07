#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//! Qt specific includes
// cppcheck-suppress missingIncludeSystem
#include <QMainWindow>

//! Qt specific macro
// cppcheck-suppress unknownMacro
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow* ui;
};
#endif // MAINWINDOW_H
