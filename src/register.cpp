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

void Register::on_next1_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void Register::on_previous1_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Register::on_next2_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void Register::on_previous2_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void Register::on_next3_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void Register::on_previous3_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void Register::on_submit_PB_clicked()
{

}

