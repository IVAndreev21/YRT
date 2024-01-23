#include "mainmenu.hpp"
#include "ui_mainmenu.h"

// Constructor of MainMenu class
MainMenu::MainMenu(QWidget* parent)
    : QWidget(parent), ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}

// Destructor of MainMenu class
MainMenu::~MainMenu()
{
    delete ui;
}

// Slot function called when the "Log In" button is clicked
void MainMenu::on_logIn_PB_clicked()
{
    // Create a new logIn window and show it, hiding the current window
    logInWindow = new logIn(nullptr);
    this->hide();
    logInWindow->show();
}

// Slot function called when the "Register" button is clicked
void MainMenu::on_register_PB_clicked()
{
    // Create a new Register window and show it, hiding the current window
    registerWindow = new Register(nullptr);
    this->hide();
    registerWindow->show();
}
