#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setWindowTitle("Register");
}

Register::~Register()
{
    delete ui;
}
