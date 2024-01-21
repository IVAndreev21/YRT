#include "mainmenu.hpp"
#include "ui_mainmenu.h"
#include <QProcess>
#include <QProcessEnvironment>
#include <QProcess>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent), ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_logIn_PB_clicked()
{
    logInWindow = new logIn(nullptr);
    this->hide();
    logInWindow->show();
}

void MainMenu::on_register_PB_clicked()
{
    registerWindow = new Register(nullptr);
    this->hide();
    registerWindow->show();
}

