#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include <QMessageBox>
logIn::logIn(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::logIn)
{
    ui->setupUi(this);
    this->setWindowTitle("Log In");
    databaseManager = std::make_unique<DatabaseManager>();
}

logIn::~logIn()
{
    delete ui;
}

void logIn::on_submit_PB_clicked()
{
}

