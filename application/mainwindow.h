#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "config_parser.h"

#include <memory>

#include <QFileDialog>
#include <QMainWindow>

//! Qt specific macro
// cppcheck-suppress unknownMacro
QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
private:
    Ui::MainWindow *ui;

    std::unique_ptr<XrayConfig> config;
    std::unique_ptr<QFileDialog> config_search;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
