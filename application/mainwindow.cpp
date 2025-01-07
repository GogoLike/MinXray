#include "mainwindow.h"

//! Qt specific includes
// cppcheck-suppress missingInclude
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    config.reset(new XrayConfig());
    config_search.reset(new QFileDialog());

    connect(this->ui->action_close, &QAction::triggered, this,
            &QMainWindow::close);
    connect(this->ui->action_import_config, SIGNAL(triggered(bool)),
            this->config_search.get(), SLOT(open()));
    connect(this->config_search.get(), &QFileDialog::fileSelected,
            this->config.get(), &XrayConfig::import_config);
}

MainWindow::~MainWindow()
{
    delete ui;
}
