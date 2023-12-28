#include "mainmenu.h"
#include "ui_mainmenu.h"
MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_LogIn_PB_clicked()
{
    logInWindow = new logIn(nullptr);
    this->hide();
    logInWindow->show();
}


void MainMenu::on_Register_PB_clicked()
{
    registerWindow = new Register(nullptr);
    this->hide();
    registerWindow->show();

}

