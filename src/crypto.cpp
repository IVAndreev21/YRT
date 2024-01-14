#include "crypto.h"
#include "ui_crypto.h"
#include "mainwindow.h"
Crypto::Crypto(std::shared_ptr<MainWindow> mainwindow, QWidget *parent)
    : QWidget(parent), ui(new Ui::Crypto), m_mainWindow(mainwindow)
{
    ui->setupUi(this);
}

Crypto::~Crypto()
{
    delete ui;
}

void Crypto::on_back_PB_clicked()
{
    this->hide();
    m_mainWindow->show();
}

