#include "mainwindow.h"

//! Qt specific includes
// cppcheck-suppress missingInclude
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    config = new XrayConfig();
    config_search = new QFileDialog();

    connect(this->ui->action_close, &QAction::triggered, this,
            &QMainWindow::close);
    connect(this->ui->action_import_config, SIGNAL(triggered(bool)),
            this->config_search, SLOT(open()));
    connect(this->config_search, &QFileDialog::fileSelected, this->config,
            &XrayConfig::import_config);
}

MainWindow::~MainWindow()
{
    delete config;
    delete config_search;
    delete ui;
}
