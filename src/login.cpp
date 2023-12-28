#include "login.h"
#include "ui_login.h"

logIn::logIn(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::logIn)
{
    ui->setupUi(this);
    this->setWindowTitle("Log In");
}

logIn::~logIn()
{
    delete ui;
}
