#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include <QMessageBox>

logIn::logIn(QWidget *parent) : QWidget(parent), ui(new Ui::logIn)
{
    ui->setupUi(this);
    ui->password_LE->setEchoMode(QLineEdit::Password);
    this->setWindowTitle("Log In");

    databaseManager = std::make_unique<DatabaseManager>();
    databaseManager->openConnection();
    db = databaseManager->getDatabase();
}

logIn::~logIn()
{
    delete ui;
}

void logIn::on_submit_PB_clicked()
{
    QString username = ui->username_LE->text();
    QString password = ui->password_LE->text();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
    qry.bindValue(":username", username);
    qry.bindValue(":password", password);

    if (qry.exec() && qry.next())
    {
        QString usernameFromDB = qry.value(15).toString();
        QString passworFromDB = qry.value(16).toString();
        QString userIBAN = qry.value(20).toString();

        if (username == usernameFromDB && password == passworFromDB)
        {
            QMessageBox::information(this, "Login Successful", "Welcome to YRT Bank! \n\nYou have successfully logged in.");
            this->hide();
            mainWindow = std::make_unique<MainWindow>(userIBAN);
            mainWindow->show();
        }
        else
        {
            QMessageBox::critical(this, "failure", "Wrong password or username");
        }
    }
}
