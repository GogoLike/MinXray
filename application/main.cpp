#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow wwindow;
    wwindow.show();
    return app.exec();
}
